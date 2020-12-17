#include "CollisionManager.hpp"
#include "CollisionGrid.hpp"
#include "BoxCollision.hpp"

#include <memory>
#include <iterator>

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
	auto cameraCBox = _camera->GetCollisionBox();
	CollisionGridCase playerCase = _grid.BoxCase(cameraCBox);
	auto& activeBoxes = _boxes[playerCase];
	//
	// [TODO] :: Short vector loop range
	//

	// Check all collisions between boxes and camera
	for (size_t i = 0; i < activeBoxes.size(); i++)
	{
		if (activeBoxes[i]->IsColliding(cameraCBox))
		{
			// If colliding, execute appropriate event
			activeBoxes[i]->OnBeginOverlap();
			_countCollision++;
		}
	}

	std::cout << _countCollision << " : " << playerCase.X << " " << playerCase.Y
			  << " ; " << activeBoxes.size() <<  std::endl;
}

void CollisionManager::AddBox(const std::shared_ptr<CollisionBox>& box)
{
	// Retrive case coordinates of the box
	CollisionGridCase boxCase = _grid.BoxCase(box);

	// Add it to the right vector
	_boxes[boxCase].push_back(box);
	box->AddIndex(boxCase, _boxes[boxCase].size() - 1);

	// Check whether the box is close to others boxes 
	if (box->X() <= boxCase.X + (_grid.WidthCase() * _grid.Margin()))
	{
		CollisionGridCase left(boxCase.X - 1, boxCase.Y);
		_boxes[left].push_back(box);
		box->AddIndex(left, _boxes[left].size() - 1);
	}
	else if (box->X() >= boxCase.X + (_grid.WidthCase() * (1.0 - _grid.Margin())))
	{
		CollisionGridCase right(boxCase.X + 1, boxCase.Y);
		_boxes[right].push_back(box);
		box->AddIndex(right, _boxes[right].size() - 1);
	}
	if (box->Y() <= boxCase.Y + (_grid.WidthCase() * _grid.Margin()))
	{
		CollisionGridCase bottom(boxCase.X, boxCase.Y - 1);
		_boxes[bottom].push_back(box);
		box->AddIndex(bottom, _boxes[bottom].size() - 1);
	}
	else if (box->Y() >= boxCase.Y + (_grid.WidthCase() * (1.0 - _grid.Margin())))
	{
		CollisionGridCase top(boxCase.X, boxCase.Y + 1);
		_boxes[top].push_back(box);
		box->AddIndex(top, _boxes[top].size() - 1);
	}	
}

void CollisionManager::DeleteBox(const std::shared_ptr<CollisionBox>& box)
{
	// Delete all references of the box in cases
	for (auto it = box->Indices().begin(); it != box->Indices().end(); ++it)
	{
		_boxes[it->first].erase(_boxes[it->first].begin() + it->second);
	}
	box->Indices().clear();
}
