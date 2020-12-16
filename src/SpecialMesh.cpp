#include "SpecialMesh.hpp"
#include "ResourceManager.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include <string>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

StaticMesh::StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName)
	: _model(model), _position(position), _shader(ResourceManager::Get().GetShader(shaderName)),
	  _cBox(std::make_shared<CollisionBox>(300, 1, 170, 10, 10, 10, []() { std::cout << "HIT CAMERA\n"; }))
{
	TransformModel();
}

void StaticMesh::TransformModel()
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
}

void StaticMesh::Draw(bool isParticuleInstance, int countParticule)
{
	Renderer::Get().SendModelMatrixUniforms(GetModelMatrix(), _shader);
	_model.Draw(_shader, isParticuleInstance, countParticule);
}

/*
* Transfromations
*/

void StaticMesh::Scale(float alpha)
{
	_modelMatrix = _modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(alpha));
}

