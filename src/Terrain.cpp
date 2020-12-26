#include "Terrain.hpp"

#include "Texture.h"
#include "Mesh.hpp"
#include "Shader.h"
#include "Fog.hpp"
#include "common.hpp"
#include "ResourceManager.hpp"
#include "LightManager.hpp"
#include "Renderer.hpp"
#include "Material.hpp"

#include "glm/glm.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

const float Terrain::_Size = 1024.0f;
const float Terrain::_MaxHeight = 100.0f;

double Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
double ModuloFloat(double a, double b);

Terrain::Terrain(float x, float z, const std::string& diffusePath, const std::string& heightmapPath)
	: _x(x), _z(z), 
	  _texture(ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE)),
	  _dataHeightmap(ResourceManager::Get().LoadHeightmap(heightmapPath, HEIGHTMAP)),
	  _mesh(generateMesh()), 
	  _shader(ResourceManager::Get().GetShader("Terrain"))
{

}

/* DRAW THE TERRAIN */
void Terrain::SendUniforms(const std::shared_ptr<Fog>& fog)
{
	_shader->Bind();

	// UV 
	_shader->SetUniform1f("uvScale", 50.0f);

	// Send Transformations Matrixes
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _shader);

	// Send Lights
	LightManager::Get().SendUniforms(_shader);

	_shader->SetUniform3f("u_SkyColor", fog->Color());
	_shader->SetUniform1f("u_fogDensity", fog->Density());
	_shader->SetUniform1f("u_fogGradient", fog->Gradient());
	_shader->SetUniform1f("u_fogHeight", fog->Height());
	_shader->SetUniform1f("u_lowerLimitFog", fog->LowerLimit());
	_shader->SetUniform1f("u_upperLimitFog", fog->UpperLimit());

	_shader->Unbind();

}

void Terrain::Draw(const std::shared_ptr<Fog>& fog)
{
	SendUniforms(fog);
	_mesh.Draw(_shader);
}

Mesh Terrain::generateMesh()
{	
	_VertexSideCount = 512;
	_GridSquareSize = _Size / (float)(_VertexSideCount - 1);

	std::vector<ShapeVertex> vertices;

	// Shape Vertex
	for (int i = 0; i < _VertexSideCount; i++) 
	{
		_heights.push_back(std::vector<float> {});
		_normals.push_back(std::vector<glm::vec3> {});

		for (int j = 0; j < _VertexSideCount; j++) 
		{
			ShapeVertex vertex;
			
			double height = GetHeightmapValue(i, j);
			_heights[i].push_back(height);

			// Positions
			vertex.position.x = (float)i / ((float)(_VertexSideCount - 1)) * _Size;
			vertex.position.y = height;
			vertex.position.z = (float)j / ((float)(_VertexSideCount - 1)) * _Size;

			// Normals
			glm::vec3 normal = CalculateNormals(i, j);
			_normals[i].push_back(normal);
			vertex.normal.x = normal.x;
			vertex.normal.y = normal.y;
			vertex.normal.z = normal.z;

			// Textures Coordinates
			vertex.texCoords.x = (float)i / (float)(_VertexSideCount - 1);
			vertex.texCoords.y = (float)j / (float)(_VertexSideCount - 1);

			vertices.push_back(vertex);
		}
	}	

	//Lerp();

	//for (int j = 0; j < _VertexSideCount; j++)
	//{
	//	std::cout << _heights[200][j] << "," << std::endl;
	//}

	// Indices
	std::vector<unsigned int> indices(6 * (_VertexSideCount - 1) * (_VertexSideCount - 1));
	int pointer = 0;
	for (int gz = 0; gz < _VertexSideCount - 1; gz++) {
		for (int gx = 0; gx < _VertexSideCount - 1; gx++) {
			int topLeft = (gx * _VertexSideCount) + gz;
			int topRight = topLeft + 1;
			int bottomLeft = ((gx + 1) * _VertexSideCount) + gz;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	
	const auto newMaterial = ResourceManager::Get().CacheBasicMaterial("Terrain", _texture.Path());
	
	return Mesh(vertices, newMaterial, indices);
}


/*
* Return the Y coordinate of the Terrain in a specific (X,Z) pixel of the heightmap
*/
float Terrain::GetHeightmapValue(int x, int z) const
{
	if (x < 0 || x >= _VertexSideCount || z < 0 || z >= _VertexSideCount)
		return 0;

	unsigned short grayscaleValue = _dataHeightmap[z * _VertexSideCount + x];
	float height = ((float)grayscaleValue / (256.0f * 256.0)) * _MaxHeight;
	
	return height;
}

double Terrain::GetHeightOfTerrain(int worldX, int worldZ) const
{
	double height = 0.0f;

	// World Position of the player relative to the terrain
	double terrainX = worldX - _x;
	double terrainZ = worldZ - _z;

	// In which case of the terrain the player is currently on
	int gridX = (int) floor(terrainX / _GridSquareSize);
	int gridZ = (int) floor(terrainZ / _GridSquareSize);

	if (gridX < 0 || gridX >= _VertexSideCount - 1 || gridZ < 0 || gridZ >= _VertexSideCount - 1)
		return height;

	// X and Z coordinates relative to the current square (between 0 and 1)
	double xCoord, zCoord;
	if (_GridSquareSize < 1.0)
		throw "Math error: Attempted to divide by Zero\n";
	else
	{
		xCoord = ModuloFloat(terrainX, _GridSquareSize) / _GridSquareSize;
		zCoord = ModuloFloat(terrainZ, _GridSquareSize) / _GridSquareSize;
	}

	// In which triangle of the square the player is currently on
	if (xCoord <= 1.0 - zCoord) 
	{
		height = Barycentre(glm::vec3(0, _heights[gridX][gridZ], 0), 
							glm::vec3(1, _heights[gridX + 1][gridZ], 0), 
							glm::vec3(0, _heights[gridX][gridZ + 1], 1), 
							glm::vec2(xCoord, zCoord));
	}
	else 
	{
		height = Barycentre(glm::vec3(1, _heights[gridX + 1][gridZ], 0),
							glm::vec3(1, _heights[gridX + 1][gridZ + 1], 1),
							glm::vec3(0, _heights[gridX][gridZ + 1], 1),
							glm::vec2(xCoord, zCoord));
	}
	return height;
}

float Terrain::GetHeightSmooth(float x, float z)
{
	float radius = 1.0f;
	return ((GetHeightOfTerrain(x, z)
		+ GetHeightOfTerrain(x + radius, z)
		+ GetHeightOfTerrain(x - radius, z)
		+ GetHeightOfTerrain(x, z + radius)
		+ GetHeightOfTerrain(x, z - radius)) / 5.0f);
}

glm::vec3 Terrain::CalculateNormals(int x, int z)
{
	float heightL = GetHeightmapValue(x - 1, z);
	float heightR = GetHeightmapValue(x + 1, z);
	float heightD = GetHeightmapValue(x, z - 1);
	float heightU = GetHeightmapValue(x, z + 1);

	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	glm::normalize(normal);
	return normal;
}

glm::vec3 Terrain::GetNormal(int worldX, int worldZ) const
{
	glm::vec3 normal(0.0f);

	// World Position of the player relative to the terrain
	float terrainX = worldX - _x;
	float terrainZ = worldZ - _z;

	// In which case of the terrain the player is currently on
	int gridX = (int)floor(terrainX / _GridSquareSize);
	int gridZ = (int)floor(terrainZ / _GridSquareSize);

	if (gridX < 0 || gridX >= _VertexSideCount - 1 || gridZ < 0 || gridZ >= _VertexSideCount - 1)
		return normal;
	else
		return _normals[gridX][gridZ];
}


double Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	double det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	double l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	double l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	double l3 = 1.0f - l1 - l2;

	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

double ModuloFloat(double a, double b)
{
	double mod;
	// Handling negative values 
	if (a < 0)
		mod = -a;
	else
		mod = a;
	if (b < 0)
		b = -b;

	// Finding mod by repeated subtraction 

	while (mod >= b)
		mod = mod - b;

	// Sign of result typically depends 
	// on sign of a. 
	if (a < 0)
		return -mod;

	return mod;
}






