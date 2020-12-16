#include "CollisionManager.hpp"
#include "CollisionGrid.hpp"
#include "BoxCollision.hpp"

#include <memory>
#include <unordered_map>

void CollisionManager::Init(FreeflyCamera * camera)
{
	_camera = camera;

	for (size_t i = 0; i < _grid.Resolution(); i++)
	{
		for (size_t j = 0; j < _grid.Resolution(); j++)
		{
			_boxes.insert({ 
				CollisionGridCase(i, j), 
				std::vector<std::shared_ptr<CollisionBox> >() 
			});
		}
	}
}

void CollisionManager::CheckCollisions()
{
	// Retrieve all active boxes from the current grid case where the player is moving
	CollisionGridCase currentCase = _grid.BoxCase(_camera->GetCollisionBox());
	auto activeBoxes = _boxes[currentCase];

	// Check all collisions between boxes and camera
	for (size_t i = 0; i < activeBoxes.size(); i++)
	{
		if (activeBoxes[i]->IsColliding(_camera))
		{
			// If colliding, execute appropriate event
			activeBoxes[i]->OnBeginOverlap();
		}
	}
}

void CollisionManager::AddBox(const std::shared_ptr<CollisionBox>& box)
{
	CollisionGridCase boxCase = _grid.BoxCase(box);
	_boxes[boxCase].push_back(box);
}
