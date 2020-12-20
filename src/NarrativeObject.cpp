#include "NarrativeObject.hpp"

NarrativeObject::NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName, const CollisionLayout& cLayout)
	: Object(model, position, cLayout), _panelName(panelName)
{

}

NarrativeObject::~NarrativeObject() {};


void NarrativeObject::Read() {
	std::cout << "read" << std::endl;
}