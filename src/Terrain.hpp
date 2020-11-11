#pragma once

#include "Mesh.hpp"
#include "Texture.h"

class Terrain
{
public:
	// Constructor
	Terrain(float x, float z, const Texture & texture);
	
	const Mesh & getMesh() const { return _mesh; }
private:
	static const float Size;
	static const int VertexCount = 128; // Vertex Count Side Terrain
	
	float _height = 0.0f;

	float   _x;
	float   _z;
	Texture _texture;
	Mesh    _mesh;

	Mesh generateMesh();

};