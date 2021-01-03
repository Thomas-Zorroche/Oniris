#pragma once

#include "engine/Model.hpp"
#include "opengl/Shader.h"
#include "collision/CollisionBox.hpp"

#include <string>
#include <memory>
#include <functional>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Fog;
class CollisionManager;

class TransformLayout
{
public:
	TransformLayout(const glm::vec3& loc, const glm::vec3& rot = glm::vec3(0, 0, 0), float scale = 1.0f, float uvScale = 1.0f)
		: _location(loc), _rotation(rot), _scale(scale), _uvScale(uvScale) {}

	glm::vec3 Location() const { return _location; }
	glm::vec3 Rotation() const { return _rotation; }
	float Scale() const { return _scale; }
	float UvScale() const { return _uvScale; }

private:
	glm::vec3 _location;
	glm::vec3 _rotation;
	float _scale;
	float _uvScale;
};



class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, const TransformLayout& transLayout, const std::string& shaderName,
		const std::shared_ptr<Fog>& fog, CollisionLayout cBoxLayout = CollisionLayout());

	void Draw(bool isParticuleInstance = false, int countParticule = 0);

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Translate(const glm::vec3& delta);
	void Scale(float alpha);
	void Rotate(const glm::vec3& alpha);

	std::shared_ptr<CollisionBox> GenerateCBox(const std::vector<ShapeVertex>& verticesCBox);
	void updateCBox();

	unsigned int GetVAO() const { return _model.GetVAO(); }

	static void SetCollisionManagerPtr(CollisionManager* cm_Ptr);

	enum RotationCBox {
		R_0, R_90, R_180, R_270
	};

private:
	void SendUniforms();

	Model _model;

	TransformLayout _transformLayout;
	glm::mat4 _modelMatrix;

	std::shared_ptr<Shader> _shader;
	float _globalRotation = 0.0f;

	CollisionLayout _cBoxLayout;
	RotationCBox _angleCBox = R_0;
	std::vector<std::shared_ptr<CollisionBox> > _cBoxes;
	
	static const std::vector<std::vector<int> > _indicesCBox;

	std::shared_ptr<Fog> _fog;

	static CollisionManager* _collisionManagerPtr;
};