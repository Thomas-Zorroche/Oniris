#include "Terrain.hpp"

#include "Texture.h"
#include "Mesh.hpp"
#include "common.hpp"

#include <vector>

const float Terrain::Size = 10.0f;

Terrain::Terrain(float x, float z, const Texture & texture)
	: _x(x), _z(z), _texture(texture), _mesh(generateMesh())
{

}

Mesh Terrain::generateMesh()
{
	int count = VertexCount * VertexCount;
	std::vector<ShapeVertex> vertices;

	// Shape Vertex
	for (int i = 0; i < VertexCount; i++) {
		for (int j = 0; j < VertexCount; j++) {
			ShapeVertex vertex;
			// Positions
			vertex.position.x = (float)j / ((float)(VertexCount - 1)) * Size;
			vertex.position.y = 0;
			vertex.position.z = (float)i / ((float)(VertexCount - 1)) * Size;

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


