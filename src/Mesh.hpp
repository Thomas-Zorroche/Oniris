#pragma once

#include <vector>
#include "common.hpp"
#include "Shader.h"
#include "Texture.h"

class Mesh
{
public:
	// Constructor
	Mesh(const std::vector<ShapeVertex> & vertices, 
		 std::vector<unsigned int>      * indices  = nullptr,	 // Optional Argument
		 std::vector<Texture>           * textures = nullptr);   // Optional Argument

	void Draw(Shader& shader);

private:
	std::vector<ShapeVertex>  _vertices;
	std::vector<unsigned int> _indices;
	std::vector<Texture>      _textures;
	
	unsigned int VAO, VBO, EBO;

	void SetupMesh();
};