#include "SpecialMesh.hpp"
#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

StaticMesh::StaticMesh(const Model& model, glm::vec3 position, const Shader & shader)
	: _model(model), _position(position), _shader(shader)
{
	TransformModel();
}

void StaticMesh::TransformModel()
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
}

void StaticMesh::Draw()
{
	_model.Draw(_shader);
}
