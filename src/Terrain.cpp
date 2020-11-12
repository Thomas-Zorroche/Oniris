#include "Terrain.hpp"

#include "Texture.h"
#include "Mesh.hpp"
#include "common.hpp"

#include <vector>
#include <iostream>

const float Terrain::_Size = 100.0f;
const float Terrain::_MaxHeight = 10.0f;
//const float Terrain::_MaxPixelColour = 256 * 256 * 256;

Terrain::Terrain(float x, float z, const Texture & texture, const Texture & heightmap)
	: _x(x), _z(z), _texture(texture), _heightmap(heightmap), _mesh(generateMesh())
{

}

Mesh Terrain::generateMesh()
{
	int VertexCount = _heightmap.GetHeight();
	std::vector<ShapeVertex> vertices;

	// Shape Vertex
	for (int i = 0; i < VertexCount; i++) {
		for (int j = 0; j < VertexCount; j++) {
			ShapeVertex vertex;
			// Positions
			vertex.position.x = (float)j / ((float)(VertexCount - 1)) * _Size;
			vertex.position.y = GetHeight(j, i);
			vertex.position.z = (float)i / ((float)(VertexCount - 1)) * _Size;

			// Normals
			vertex.normal.x = 0;
			vertex.normal.y = 1;
			vertex.normal.z = 0;

			// Textures Coordinates
			vertex.texCoords.x = (float)j / (float)(VertexCount - 1);
			vertex.texCoords.y = (float)i / (float)(VertexCount - 1);

			vertices.push_back(vertex);
		}
	}
	
	// Indices
	std::vector<unsigned int> indices(6 * (VertexCount - 1) * (VertexCount - 1));
	int pointer = 0;
	for (int gz = 0; gz < VertexCount - 1; gz++) {
		for (int gx = 0; gx < VertexCount - 1; gx++) {
			int topLeft = (gz * VertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * VertexCount) + gx;
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
float Terrain::GetHeight(int x, int z) const
{
	if (x < 0 || x >= _heightmap.GetHeight() || z < 0 || z >= _heightmap.GetHeight())
		return 0;

	float redValue = _heightmap.GetRGB(x, z);
	float height = ((redValue / 255.0f) * (2 * _MaxHeight)) - _MaxHeight;
	//std::cout << height << std::endl;
	
	return height;

}


