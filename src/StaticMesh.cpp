#include "StaticMesh.hpp"
#include "ResourceManager.hpp"
#include "CollisionManager.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include <string>
#include <vector>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


const std::vector<std::vector<int> > StaticMesh::_indicesCBox = { 
	{0, 11, 3, 1}, {3, 0, 7, 1}, {7, 3, 11, 1 }, {11, 7, 0, 1} 
};

StaticMesh::StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName, CollisionLayout cBoxLayout)
	: _model(model), _position(position), _shader(ResourceManager::Get().GetShader(shaderName)),
	  _modelMatrix(glm::mat4(1.0f)), 
	  _cBoxLayout(cBoxLayout), _cBox(nullptr)
{
	if (_cBoxLayout.HasCollision())
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
	{
		_globalRotation += alpha;
		if ((int)_globalRotation % 90 != 0 || _globalRotation < 0 || _globalRotation > 270)
			throw std::string("Impossible to rotate to this angle due to the Collision Box.");
		_angleCBox = (RotationCBox)(_globalRotation / 90.0f);
		updateCBox();
	}
}

/*
* Collision Box
*/
void StaticMesh::GenerateCBox(const std::vector<ShapeVertex>& verticesCBox)
{
	// Indices
	size_t i_origin = _indicesCBox[(int)_angleCBox][0];
	size_t i_w = _indicesCBox[(int)_angleCBox][1];
	size_t i_d = _indicesCBox[(int)_angleCBox][2];
	size_t i_h = _indicesCBox[(int)_angleCBox][3];
	
	// Retrieve x, y, z of the fist vertex
	glm::vec3 origin;
	origin.x = verticesCBox[i_origin].position.x;
	origin.y = verticesCBox[i_origin].position.y;
	origin.z = verticesCBox[i_origin].position.z;

	// Compute w, h, d
	float w = abs(verticesCBox[i_w].position.x - verticesCBox[i_origin].position.x);
	float h = abs(verticesCBox[i_h].position.y - verticesCBox[i_origin].position.y);
	float d = abs(verticesCBox[i_d].position.z - verticesCBox[i_origin].position.z);

	// Create and return the Collision Box
	_cBox = std::make_shared<CollisionBox>(origin, w, h, d, _cBoxLayout.Function(), _cBoxLayout.CanStopMovement());

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

