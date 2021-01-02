#pragma once

#include "collision/CollisionBox.hpp"
#include "collision/CollisionGrid.hpp"

#include "engine/Camera.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

class Camera;

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions();
	void AddBox(const std::shared_ptr<CollisionBox>& box);
	void DeleteBox(const std::shared_ptr<CollisionBox>& box);
	
	void DrawCBoxes();
	void DebugMode();

	void SetCamera(const std::shared_ptr<Camera>& cameraPtr);
	
private:
	void updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadBox);

	CollisionGrid _grid;
	std::unordered_map<CollisionGridCase, std::vector<std::shared_ptr<CollisionBox> >> _boxes;
	std::shared_ptr<Camera> _camera;

	// Debug Attributes
	bool _debugMode = false;
};


