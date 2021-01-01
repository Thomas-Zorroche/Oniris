#include "engine/Terrain.hpp"

#include "opengl/Texture.h"
#include "opengl/Mesh.hpp"
#include "opengl/Shader.h"
#include "engine/Fog.hpp"
#include "common.hpp"
#include "engine/ResourceManager.hpp"
#include "lighting/LightManager.hpp"
#include "engine/Renderer.hpp"
#include "engine/Material.hpp"

#include "glm/glm.hpp"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

const float Terrain::_Size = 1024.0f;
const float Terrain::_MaxHeight = 100.0f;

double Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
double ModuloFloat(double a, double b);

Terrain::Terrain(float x, float z, const std::string& heightmapPath)
	: _x(x), _z(z), 
	  _dataHeightmap(ResourceManager::Get().LoadHeightmap(heightmapPath, HEIGHTMAP)),
	  _mesh(generateMesh()), 
	  _shader(ResourceManager::Get().GetShader("Terrain"))
{

}

/* DRAW THE TERRAIN */
void Terrain::SendUniforms(const std::shared_ptr<Fog>& fog)
{
	_shader->Bind();

	// Textures
	auto material = _mesh.MaterialPtr();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(_shader->getID(), "backgroundTexture"), 0);
	glBindTexture(GL_TEXTURE_2D, material->GetParameterTexture(0));
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(_shader->getID(), "rTexture"), 1);
	glBindTexture(GL_TEXTURE_2D, material->GetParameterTexture(1));
	glActiveTexture(GL_TEXTURE2);
	glUniform1i(glGetUniformLocation(_shader->getID(), "gTexture"), 2);
	glBindTexture(GL_TEXTURE_2D, material->GetParameterTexture(2));
	glActiveTexture(GL_TEXTURE3);
	glUniform1i(glGetUniformLocation(_shader->getID(), "bTexture"), 3);
	glBindTexture(GL_TEXTURE_2D, material->GetParameterTexture(3));
	glActiveTexture(GL_TEXTURE4);
	glUniform1i(glGetUniformLocation(_shader->getID(), "blendmap"), 4);
	glBindTexture(GL_TEXTURE_2D, material->GetParameterTexture(4));

	// UV 
	_shader->SetUniform1f("uvScale", 65.0f);

	// Send Transformations Matrixes
	Renderer::Get().SendTransMatrixUniforms(glm::mat4(1.0f), _shader);

	// Send Lights
	LightManager::Get().SendUniforms(_shader);

	_shader->SetUniform3f("fog.colorShadow", fog->Color().first);
	_shader->SetUniform3f("fog.colorSun", fog->Color().second);
	_shader->SetUniform1f("fog.lowerLimitFog", fog->LowerLimit());
	_shader->SetUniform1f("fog.upperLimitFog", fog->UpperLimit());

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
	
	std::vector<std::string> filepaths = {
		"res/img/Terrain/Grass.png",
		"res/img/Terrain/Bricks.png",
		"res/img/Terrain/Cliff.png",
		"res/img/Terrain/Sand.jpg",
		"res/img/Terrain/blendmap.png"
	};
	const auto newMaterial = ResourceManager::Get().CacheMultipleTexMaterial("Terrain", filepaths);
	
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

//
// [TODO] : replace with fmod
//
double ModuloFloat(double a, double b)
{
	double mod;
	if (a < 0)
		mod = -a;
	else
		mod = a;
	if (b < 0)
		b = -b;

	while (mod >= b)
		mod = mod - b;

	if (a < 0)
		return -mod;

	return mod;
}






