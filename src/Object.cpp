#include "Object.hpp"
#include "ResourceManager.hpp"
#include "StaticMesh.hpp"
#include "InputHandler.hpp"

Object::Object(const Model& model, const TransformLayout& transLayout)
	:_staticMesh(std::make_shared<StaticMesh>(model, transLayout, "Key", nullptr, CollisionLayout(true, false, false, this)))
{

}

Object::~Object() {

}

void Object::Draw() {
	_staticMesh->Draw();
}
