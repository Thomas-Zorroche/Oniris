#include "Object.hpp"
#include "ResourceManager.hpp"
#include "StaticMesh.hpp"
#include "InputHandler.hpp"

Object::Object(const Model& model, const glm::vec3& position) 
	:_staticMesh(std::make_shared<StaticMesh>(model, position, "Key", CollisionLayout(true, false, false, this)))
{

}

Object::~Object() {

}

void Object::Draw() {
	_staticMesh->Draw();
}
