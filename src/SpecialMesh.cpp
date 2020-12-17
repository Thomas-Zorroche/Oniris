#include "SpecialMesh.hpp"
#include "ResourceManager.hpp"
#include "CollisionManager.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include <string>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

StaticMesh::StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName, 
					   const OnBeginOverlapFunction& function, bool hasCollision)
	: _model(model), _position(position), _shader(ResourceManager::Get().GetShader(shaderName)),
	  _modelMatrix(glm::mat4(1.0f)), 
	  _hasCollision(hasCollision), _collisionFunction(function), _cBox(nullptr)
{
	if (_hasCollision)
	{
		// Try to generate a collision box, if there is one.
		try
		{
			GenerateCBox(_model.VerticesCBox());
		}
		catch (const std::string& e)
		{
			std::cerr << "[StaticMesh] :: " << e << std::endl;
		}
	}

	// Translate the mesh to the correct location
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
	if (_cBox)
		updateCBox();
}

void StaticMesh::Translate(const glm::vec3& delta)
{
	_modelMatrix = _modelMatrix * glm::translate(glm::mat4(1.0f), delta);
	if (_cBox)
		updateCBox();
}

void StaticMesh::Rotate(float alpha, const glm::vec3& axis)
{
	_modelMatrix = _modelMatrix * glm::rotate(glm::mat4(1.0f), glm::radians(alpha), axis);
	if (_cBox)
		updateCBox();
}

/*
* Collision Box
*/
void StaticMesh::GenerateCBox(const std::vector<ShapeVertex>& verticesCBox)
{
	// Retrieve x, y, z of the fist vertex
	glm::vec3 origin;
	origin.x = verticesCBox[0].position.x;
	origin.y = verticesCBox[0].position.y;
	origin.z = verticesCBox[0].position.z;

	// Compute w, h, d
	float w = abs(verticesCBox[11].position.x - verticesCBox[0].position.x);
	float h = abs(verticesCBox[1].position.y - verticesCBox[0].position.y);
	float d = abs(verticesCBox[3].position.z - verticesCBox[0].position.z);

	// Create and return the Collision Box
	_cBox = std::make_shared<CollisionBox>(origin, w, h, d, _collisionFunction);

	CollisionManager::Get().AddBox(_cBox);
}

void StaticMesh::updateCBox()
{
	// Transform cBox Mesh
	std::vector<ShapeVertex> newVertices;
	for (const auto& vertex : _model.VerticesCBox())
	{
		newVertices.push_back(glm::vec3(_modelMatrix * glm::vec4(vertex.position, 1)));
	}

	// Remove cBox inside all the cases where the cBox was
	CollisionManager::Get().DeleteBox(_cBox);

	// Compute the new cBox
	GenerateCBox(newVertices);
}

