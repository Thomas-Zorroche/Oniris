#include "NarrativeObject.hpp"

NarrativeObject::NarrativeObject(const Model& model, const glm::vec3& position, const std::string& panelName)
	: Object(model, position), _panelName(panelName)
{

}

NarrativeObject::~NarrativeObject() {};


void NarrativeObject::Read() {
	std::cout << "read" << std::endl;
}