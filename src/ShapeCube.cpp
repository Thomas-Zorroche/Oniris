#include "ShapeCube.hpp"

ShapeCube::ShapeCube(const glm::vec3& origin, float w, float h, float d)
	: _origin(origin), _w(w), _h(h), _d(d), 
	  _vertices(std::vector<ShapeVertex>()), _indices(std::vector<unsigned int>())
{
	GenerateVertices();
}

void ShapeCube::GenerateVertices()
{
	// Generate Vertices
	// =====================================================================
	// Bottom Face
	_vertices.push_back(ShapeVertex(_origin));							// 0
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(_w, 0, 0)));	// 1
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(0, 0, -_d)));   // 2
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(_w, 0, -_d)));  // 3

	// Top Face
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(0, _h, 0)));	// 4
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(_w, _h, 0)));	// 5
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(0, _h, -_d)));  // 6
	_vertices.push_back(ShapeVertex(_origin + glm::vec3(_w, _h, -_d))); // 7

	// Generate Indices
	// =====================================================================
	_indices = std::vector<unsigned int >{
		0, 1, 4,	// Front Face
		4, 1, 5,

		1, 3, 5,	// Left Face
		5, 3, 7,

		3, 2, 7,	// Back Face
		7, 2, 6,

		2, 0, 6,	// Right Face
		6, 0, 4,

		0, 1, 2,	// Bottom Face
		2, 1, 3, 

		4, 5, 6,	// Top Face
		6, 5, 7
	};
}