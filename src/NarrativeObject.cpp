#include "NarrativeObject.hpp"

NarrativeObject::NarrativeObject(const Model& model, glm::vec3 position, CollisionLayout cLayout)
	: Object(model, position, cLayout)
{

}

NarrativeObject::~NarrativeObject() {};


void NarrativeObject::Read() {
	std::cout << "read" << std::endl;
}