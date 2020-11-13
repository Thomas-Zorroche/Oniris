#include "Terrain.hpp"

#include "Texture.h"
#include "Mesh.hpp"
#include "common.hpp"

#include "glm/glm.hpp"

#include <vector>
#include <iostream>

const float Terrain::_Size = 300.0f;
const float Terrain::_MaxHeight = 15.0f;
//const float Terrain::_MaxPixelColour = 256 * 256 * 256;

float Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

Terrain::Terrain(float x, float z, const Texture & texture, const Texture & heightmap)
	: _x(x), _z(z), _texture(texture), _heightmap(heightmap), _mesh(generateMesh())
{

}

Mesh Terrain::generateMesh()
{
	_VertexSideCount = _heightmap.GetHeight();
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
			float height = GetHeightmapValue(j, i);
			//_heights[j][i] = height;
			_heights[i].push_back(height);
			
			// Positions
			vertex.position.x = (float)i / ((float)(_VertexSideCount - 1)) * _Size;
			vertex.position.y = height;
			vertex.position.z = (float)j / ((float)(_VertexSideCount - 1)) * _Size;

			// Normals
			vertex.normal.x = 0;
			vertex.normal.y = 1;
			vertex.normal.z = 0;

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
			int topLeft = (gz * _VertexSideCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * _VertexSideCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	
	/*
	* ATTENTION : Texture Copy Constructeur x4 !!!
	*/
	std::vector<Texture> ArrayTextures = { _texture };

	return Mesh(vertices, &indices, &ArrayTextures);
}

/*
* Return the Y coordinate of the Terrain in a specific (X,Z) pixel of the heightmap
*/
float Terrain::GetHeightmapValue(int x, int z) const
{
	if (x < 0 || x >= _heightmap.GetHeight() || z < 0 || z >= _heightmap.GetHeight())
		return 0;

	float redValue = _heightmap.GetRGB(x, z);
	float height = ((redValue / 255.0f) * (2 * _MaxHeight)) - _MaxHeight;
	//std::cout << height << std::endl;
	
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

float Barycentre(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;

	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}



