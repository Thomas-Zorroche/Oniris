#pragma once

#include <vector>
#include <memory>
#include "common.hpp"
#include "opengl/Shader.h"
//#include "engine/Material.hpp"

class Material;

class Mesh
{
public:
	Mesh(const std::vector<ShapeVertex> & vertices, 
		 const std::shared_ptr<Material>& material,
		 const std::vector<unsigned int>& indices  = std::vector<unsigned int>());   // Optional Argument

	void Free();

	void Draw(std::shared_ptr<Shader>& shader, bool IsParticuleInstance = false, int countParticules = 0) const;

	unsigned int GetVAO() const { return VAO; }
	const std::vector<ShapeVertex>& Vertices() const { return _vertices; }
	std::vector<ShapeVertex>& Vertices() { return _vertices; }

	const std::shared_ptr<Material>& MaterialPtr() const { return _material; }


private:
	std::vector<ShapeVertex>  _vertices;
	std::vector<unsigned int> _indices;
	
	unsigned int VAO, VBO, EBO;

	std::shared_ptr<Material> _material;

	void SetupMesh();
};