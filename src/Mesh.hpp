#pragma once

#include <vector>
#include "common.hpp"
#include "Shader.h"

class Mesh
{
public: 
	std::vector<ShapeVertex> _vertices;
	unsigned int VAO;

	// Constructor
	Mesh(std::vector<ShapeVertex> vertices);

	void Draw(Shader& shader);

private:
	unsigned int VBO;

	void SetupMesh();

};