#pragma once

#include "Mesh.hpp"
#include "Texture.h"

class Terrain
{
public:
	// Constructor
	Terrain(float x, float z, const Texture & texture, const Texture& heightmap);
	
	const Mesh & getMesh() const { return _mesh; }
	float GetHeight(int x, int y) const;
private:
	static const float _Size;
	static const float _MaxHeight;
	static const float _MaxPixelColour;

	
	float _height = 0.0f;
	float   _x;
	float   _z;
	Texture _texture;
	Texture _heightmap;
	Mesh    _mesh;


	Mesh generateMesh();

};