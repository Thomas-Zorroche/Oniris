#pragma once

#include <vector>
#include "common.hpp"
#include "glm/glm.hpp"

class ShapeCube
{
public:
	ShapeCube(const glm::vec3& origin, float w, float h, float d);

	const std::vector<ShapeVertex>& Vertices() const { return _vertices; }
	const std::vector<unsigned int>& Indices() const { return _indices; }

	void GenerateVertices();

private:
	glm::vec3 _origin;
	float _w;
	float _h;
	float _d;

	std::vector<ShapeVertex> _vertices;
	std::vector<unsigned int> _indices;
};
