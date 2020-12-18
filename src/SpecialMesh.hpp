#pragma once

#include "Model.hpp"
#include "Shader.h"
#include "BoxCollision.hpp"

#include <string>
#include <memory>
#include <functional>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, glm::vec3 position, const std::string& shaderName, 
			   const OnBeginOverlapFunction& function = [] {}, bool hasCollision = false);

	void Draw(bool isParticuleInstance = false, int countParticule = 0);

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Translate(const glm::vec3& delta);
	void Scale(float alpha);
	void Rotate(float alpha, const glm::vec3& axis);

	void StaticMesh::GenerateCBox(const std::vector<ShapeVertex>& verticesCBox);
	void StaticMesh::updateCBox();

	unsigned int GetVAO() const { return _model.GetVAO(); }

	enum RotationCBox {
		R_0, R_90, R_180, R_270
	};

private:
	Model _model;
	glm::vec3 _position;
	glm::mat4 _modelMatrix;
	std::shared_ptr<Shader> _shader;
	float _globalRotation = 0.0f;

	OnBeginOverlapFunction _collisionFunction;
	RotationCBox _angleCBox = R_0;
	bool _hasCollision;
	std::shared_ptr<CollisionBox> _cBox;
	
	//static const float _indicesCBox[4][4];
	static const std::vector<std::vector<int> > _indicesCBox;
};