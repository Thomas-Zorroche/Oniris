#include "Terrain.hpp"

#include "Texture.h"
#include "Mesh.hpp"
#include "Shader.h"
#include "Fog.hpp"
#include "common.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Material.hpp"

#include "glm/glm.hpp"

#include <vector>
#include <iostream>
#include <string>

const float Terrain::_Size = 1000.0f;
const float Terrain::_MaxHeight = 100.0f;
const float Terrain::_MaxPixelColour = 256 * 256 * 256;

float Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

Terrain::Terrain(float x, float z, const std::string& diffusePath, const std::string& heightmapPath)
	: _x(x), _z(z), 
	  _texture(ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE)),
	  _heightmap(ResourceManager::Get().LoadTexture(heightmapPath, DIFFUSE)),
	  _mesh(generateMesh()), 
	  _shader(ResourceManager::Get().GetShader("Terrain"))
{
}

Mesh Terrain::generateMesh()
{	
	_VertexSideCount = _heightmap.Height();
	_GridSquareSize = _Size / (float)(_VertexSideCount - 1);

	std::vector<ShapeVertex> vertices;

	// Shape Vertex
	for (int i = 0; i < _VertexSideCount; i++) 
	{
		_heights.push_back(std::vector<float> {});

		for (int j = 0; j < _VertexSideCount; j++) 
		{
			ShapeVertex vertex;

			// Height
			float height = GetHeightmapValue(i, j);
			//_heights[j][i] = height;
			_heights[i].push_back(height);
			
			// Positions
			vertex.position.x = (float)i / ((float)(_VertexSideCount - 1)) * _Size;
			vertex.position.y = height;
			vertex.position.z = (float)j / ((float)(_VertexSideCount - 1)) * _Size;

			// Normals
			glm::vec3 normal = CalculateNormals(i, j);
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
	
	const auto newMaterial = ResourceManager::Get().CacheBasicMaterial("Terrain", _texture.Path());
	
	return Mesh(vertices, newMaterial, indices);
}


/*
* Return the Y coordinate of the Terrain in a specific (X,Z) pixel of the heightmap
*/
float Terrain::GetHeightmapValue(int x, int z) const
{
	if (x < 0 || x >= _heightmap.Height() || z < 0 || z >= _heightmap.Height())
		return 0;

	float redValue = _heightmap.GetRGB(x, z);
	float height = (redValue / 255.0f) * _MaxHeight;
	
	return height;
}

float Terrain::GetHeightOfTerrain(int worldX, int worldZ) const
{
	float height = 0.0f;

	// World Position of the player relative to the terrain
	float terrainX = worldX - _x;
	float terrainZ = worldZ - _z;

	// In which case of the terrain the player is currently on
	int gridX = (int) floor(terrainX / _GridSquareSize);
	int gridZ = (int) floor(terrainZ / _GridSquareSize);

	if (gridX < 0 || gridX >= _VertexSideCount - 1 || gridZ < 0 || gridZ >= _VertexSideCount - 1)
		return height;

	// X and Z coordinates relative to the current square (between 0 and 1)
	float xCoord, zCoord;
	if (_GridSquareSize < 1)
		throw "Math error: Attempted to divide by Zero\n";
	else
	{
		xCoord = ((int)terrainX % (int)_GridSquareSize) / _GridSquareSize;
		zCoord = ((int)terrainZ % (int)_GridSquareSize) / _GridSquareSize;
	}

	// In which triangle of the square the player is currently on
	if (xCoord <= 1 - zCoord) 
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


float Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;

	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}


/* DRAW THE TERRAIN */
void Terrain::Draw(const std::shared_ptr<Fog>& fog)
{
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _shader);
	Renderer::Get().SendBlinnPhongUniforms(_shader);
	_shader->Bind();
	_shader->SetUniform3f("u_SkyColor", fog->Color());
	_shader->SetUniform1f("u_fogDensity", fog->Density());
	_shader->SetUniform1f("u_fogGradient", fog->Gradient());
	_mesh.Draw(_shader);
}

