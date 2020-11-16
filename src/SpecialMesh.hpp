#pragma once

#include "Model.hpp"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, glm::vec3 position, const Shader& shader);

	void Draw();

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	Shader & GetShader() { return _shader; }

private:
	Model _model;
	glm::vec3 _position;
	glm::mat4 _modelMatrix;
	Shader _shader;
	
	void TransformModel();
};