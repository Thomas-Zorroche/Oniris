#pragma once

#include <vector>
#include <memory>
#include "common.hpp"
#include "Shader.h"
//#include "Material.hpp"

class Material;

class Mesh
{
public:
	Mesh();

	Mesh(const std::vector<ShapeVertex> & vertices, 
		 const std::shared_ptr<Material>& material,
		 std::vector<unsigned int>      * indices  = nullptr);   // Optional Argument

	//Mesh(const Mesh& m);
	
	void Draw(std::shared_ptr<Shader>& shader, bool IsParticuleInstance = false, int countParticules = 0) const;

	unsigned int GetVAO() const { return VAO; }
	const std::vector<ShapeVertex>& Vertices() const { return _vertices; }


private:
	std::vector<ShapeVertex>  _vertices;
	std::vector<unsigned int> _indices;
	
	unsigned int VAO, VBO, EBO;

	std::shared_ptr<Material> _material;

	void SetupMesh();
};