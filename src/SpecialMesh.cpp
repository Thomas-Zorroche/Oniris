#include "SpecialMesh.hpp"
#include "ResourceManager.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include <string>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

StaticMesh::StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName, const OnBeginOverlapFunction& function)
	: _model(model), _position(position), _shader(ResourceManager::Get().GetShader(shaderName)),
	  _modelMatrix(glm::mat4(1.0f)),
	  _cBox(GenerateCBox(function))
{
	Translate(_position);
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

void StaticMesh::Translate(const glm::vec3& delta)
{
	_modelMatrix = _modelMatrix * glm::translate(glm::mat4(1.0f), delta);;
}

/*
* Collision Box
*/
std::shared_ptr<CollisionBox> StaticMesh::GenerateCBox(const OnBeginOverlapFunction& collisionFunction)
{
	// Retrieve vertices of Collision Box of Model
	std::vector<ShapeVertex> verticesCBox(_model.VerticesCBox());

	// Retrieve x, y, z of the fist vertex
	glm::vec3 origin;
	origin.x = verticesCBox[0].position.x;
	origin.y = verticesCBox[0].position.y;
	origin.z = verticesCBox[0].position.z;

	// Compute w, h, d
	float w = verticesCBox[4].position.x - verticesCBox[0].position.x;
	float h = verticesCBox[1].position.y - verticesCBox[0].position.y;
	float d = verticesCBox[2].position.z - verticesCBox[0].position.z;

	// Create and return the Collision Box
	return std::make_shared<CollisionBox>(origin, w, h, d, collisionFunction);
}

