#pragma once

#include "gameplay/InteractiveObject.hpp"
#include "lighting/LightManager.hpp"
#include "engine/AudioManager.hpp"


class StaticMesh;

class IODoor : public InteractiveObject
{
public:
	IODoor(const Model& model, const TransformLayout& transLayout, const std::string& panelName, const std::shared_ptr<StaticMesh>& ioObject)
		: InteractiveObject(model, transLayout, panelName, ioObject) {};
	

private:
	void Interact();
	bool _open = false;

};

void IODoor::Interact()
{
	AudioManager::Get().Play("res/audio/door.mp3", 0.2, false);

	if (_open)
	{
		_open = false;
		_panelName = "p_open";
		_ioObject->Rotate(glm::vec3(0, -90, 0));
	}
	else
	{
		_open = true;
		_panelName = "p_close";
		_ioObject->Rotate(glm::vec3(0, 90, 0));
	}
}