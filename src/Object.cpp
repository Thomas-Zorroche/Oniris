#include "Object.hpp"
#include "ResourceManager.hpp"

Object::Object(const Model& model, const glm::vec3& position, const CollisionLayout& cLayout) {

	_Mesh = std::make_shared<StaticMesh>(model, position, "Key", cLayout);
}

Object::~Object() {

}

void Object::Draw() {
	_Mesh->Draw();
}