#include "engine/StaticMesh.hpp"
#include "engine/ResourceManager.hpp"
#include "collision/CollisionManager.hpp"
#include "lighting/LightManager.hpp"
#include "opengl/Shader.h"
#include "engine/Renderer.hpp"
#include "engine/Fog.hpp"

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"




StaticMesh::StaticMesh(const Model& model, const TransformLayout& transLayout, const std::string& shaderName,
	const std::shared_ptr<Fog>& fog, CollisionLayout cBoxLayout)
	: _model(model), _transformLayout(transLayout), _shader(ResourceManager::Get().GetShader(shaderName)),
	  _modelMatrix(glm::mat4(1.0f)), 
	  _cBoxLayout(cBoxLayout), _cBoxes(std::vector<std::shared_ptr<CollisionBox> >()),
	  _fog(fog)
{
	if (_cBoxLayout.HasCollision())
	{
		// Try to generate collision boxes
		try
		{
			for (size_t i = 0; i < _model.CBoxes().size(); i++)
			{
				_cBoxes.push_back(GenerateCBox(_model.VerticesCBox(i)));
			}
		}
		catch (const std::string& e)
		{
			std::cerr << "[StaticMesh] :: " << e << std::endl;
		}
	}

	// Translate the mesh to the correct location
	Translate(_transformLayout.Location(), false);
	Rotate(_transformLayout.Rotation(), false);
	Scale(_transformLayout.Scale(), false);
	if (_cBoxLayout.HasCollision())
		updateCBox();
}

void StaticMesh::Draw(bool isParticuleInstance, int countParticule)
{
	SendUniforms();
	_model.Draw(_shader, isParticuleInstance, countParticule);
}

/*
* Transfromations
*/

void StaticMesh::Scale(float alpha, bool dynamic)
{
	_modelMatrix = _modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(alpha));
	if (alpha != 1.0f && _cBoxLayout.HasCollision() && dynamic)
		updateCBox();
}

void StaticMesh::Translate(const glm::vec3& delta, bool dynamic)
{
	_modelMatrix = _modelMatrix * glm::translate(glm::mat4(1.0f), delta);
	if (_cBoxLayout.HasCollision() && dynamic)
		updateCBox();
}

void StaticMesh::Rotate(const glm::vec3& alpha, bool dynamic)
{
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.x), glm::vec3(1, 0, 0));
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.y), glm::vec3(0, 1, 0));
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.z), glm::vec3(0, 0, 1));

	if (_cBoxLayout.HasCollision())
	{
		_globalRotation += (alpha.x + alpha.y + alpha.z);
		
		int angle = (int)(_globalRotation / 90);
		angle -= 4 * (angle / 4);
		_angleCBox = (RotationCBox)(angle);

		if (dynamic && _globalRotation != 0.0f)
			updateCBox();
	}
}

/*
* Uniforms
*/
void StaticMesh::SendUniforms()
{
	_shader->Bind();

	// UV 
	_shader->SetUniform1f("uvScale", 1.0f);

	// Send Transformations Matrixes
	Renderer::Get().SendTransMatrixUniforms(GetModelMatrix(), _shader);

	// Send Lights
	LightManager::Get().SendUniforms(_shader);

	// Send Fog
	if (_fog)
	{
		_shader->SetUniform3f("fog.colorShadow", _fog->Color().first);
		_shader->SetUniform3f("fog.colorSun", _fog->Color().second);
		_shader->SetUniform1f("fog.lowerLimitFog", _fog->LowerLimit());
		_shader->SetUniform1f("fog.upperLimitFog", _fog->UpperLimit());
	}

	_shader->Unbind();
}

/*
* Collision Box
*/
std::shared_ptr<CollisionBox> StaticMesh::GenerateCBox(const std::vector<ShapeVertex>& verticesCBox)
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

	// Create the Collision Box
	return std::make_shared<CollisionBox>(origin, w, h, d, _cBoxLayout);
}

void StaticMesh::updateCBox()
{
	for (size_t i = 0; i < _model.CBoxes().size(); i++)
	{
		// Transform cBox Mesh
		std::vector<ShapeVertex> newVertices;
		for (const auto& vertex : _model.VerticesCBox(i))
		{
			newVertices.push_back(glm::vec3(_modelMatrix * glm::vec4(vertex.position, 1)));
		}

		// Remove cBox inside all the cases where the cBox was
		_collisionManagerPtr->DeleteBox(_cBoxes[i]);

		// Compute the new cBox
		_cBoxes[i] = GenerateCBox(newVertices);

		//std::vector<std::shared_ptr<CollisionBox> >::iterator it = _cBoxes.end();
		_collisionManagerPtr->AddBox(_cBoxes[i]);

		//_cBoxes[i]->updateDebugMesh();
	}
}


/*
* Static Data
*/
CollisionManager* StaticMesh::_collisionManagerPtr = nullptr;

void StaticMesh::SetCollisionManagerPtr(CollisionManager* cm_Ptr)
{
	_collisionManagerPtr = cm_Ptr;
}

const std::vector<std::vector<int> > StaticMesh::_indicesCBox = {
	{0, 11, 3, 1}, {3, 0, 7, 1}, {7, 3, 11, 1 }, {11, 7, 0, 1}
};


/*
* Free Memory of model
*/
void StaticMesh::Free()
{
	_model.Free();
}

