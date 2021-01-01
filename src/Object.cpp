#include "Object.hpp"
#include "ResourceManager.hpp"
#include "StaticMesh.hpp"
#include "InputHandler.hpp"


Object::Object(const Model& model, const TransformLayout& transLayout, const std::string& shaderName)
	:_staticMesh(std::make_shared<StaticMesh>(model, transLayout, shaderName, nullptr, CollisionLayout(true, false, false, this)))
{

}

Object::~Object() {

}

void Object::Draw() {
	_staticMesh->Draw();
}
