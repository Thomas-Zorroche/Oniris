#include "Object.hpp"
#include "ResourceManager.hpp"

Object::Object(const Model& model, glm::vec3 position, CollisionLayout cLayout) {

	_Mesh = std::make_shared<StaticMesh>(model, position, "Key", nullptr, cLayout);
}

Object::~Object() {

}

void Object::Draw() {
	_Mesh->Draw();
}