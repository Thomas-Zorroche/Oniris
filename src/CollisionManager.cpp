#include "CollisionManager.hpp"
#include "CollisionGrid.hpp"
#include "CollisionBox.hpp"
#include "Hud.hpp"

#include <memory>
#include <iterator>

void CollisionManager::Init(Camera* camera)
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

	// Check all collisions between boxes and camera
	std::vector<HitCollisionAxis> AxisHit;
	int countCollision = 0;
	for (size_t i = 0; i < activeBoxes.size(); i++)
	{
		HitResult hit = activeBoxes[i]->IsColliding(cameraCBox);
		if (hit.IsHitting)
		{
			// If colliding, execute appropriate event
			if (activeBoxes[i]->StopMovement())
				AxisHit.push_back(hit.Axis);
			activeBoxes[i]->OnBeginOverlap();
			countCollision++;
		}
	}

	if (AxisHit.empty())
		AxisHit.push_back(NONE);

	if (countCollision == 0)
	{
		Hud::Get().SetState(ScreenState::INGAME);
	}
	
	_camera->BlockMovement(AxisHit);

	if (_debugMode)
		DrawCBoxes();
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
		updateCaseIndices(it->first, it->second);
	}
	box->Indices().clear();
}

void CollisionManager::updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadBox)
{
	for (size_t i = indexDeadBox; i < _boxes[gridCase].size(); i++)
		_boxes[gridCase][i]->DecreaseIndexCase(gridCase);
}

void CollisionManager::DrawCBoxes()
{
	for (auto it = _boxes.begin(); it != _boxes.end(); ++it)
	{
		for (auto& box : it->second)
			box->Draw();
	}
}

void CollisionManager::DebugMode()
{
	if (_debugMode)
		_debugMode = false;
	else
		_debugMode = true;
}