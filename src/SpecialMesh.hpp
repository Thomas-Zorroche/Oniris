#pragma once

#include "Model.hpp"
#include "Shader.h"
#include "BoxCollision.hpp"

#include <string>
#include <memory>
#include <functional>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName, const OnBeginOverlapFunction& function = [] {});

	void Draw(bool isParticuleInstance = false, int countParticule = 0);

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Translate(const glm::vec3& delta);
	void Scale(float alpha);
	void Rotate(float alpha, const glm::vec3& axis);

	std::shared_ptr<CollisionBox> StaticMesh::GenerateCBox(const OnBeginOverlapFunction& collisionFunction);

	unsigned int GetVAO() const { return _model.GetVAO(); }


private:
	Model _model;
	glm::vec3 _position;
	glm::mat4 _modelMatrix;
	std::shared_ptr<Shader> _shader;

	std::shared_ptr<CollisionBox> _cBox;
};