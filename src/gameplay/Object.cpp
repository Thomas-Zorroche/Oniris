#include "gameplay/Object.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/StaticMesh.hpp"
#include "engine/InputHandler.hpp"


Object::Object(const Model& model, const TransformLayout& transLayout, const std::string& shaderName)
	:_staticMesh(std::make_shared<StaticMesh>(model, transLayout, shaderName, nullptr, CollisionLayout(true, false, false, this)))
{

}

Object::~Object() {

}

void Object::Draw() {
	_staticMesh->Draw();
}
