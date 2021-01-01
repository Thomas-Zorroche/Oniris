#pragma once

#include "collision/CollisionBox.hpp"
#include "collision/CollisionGrid.hpp"

#include "engine/Camera.hpp"

#include <vector>
#include <memory>
#include <unordered_map>


class CollisionManager
{
public:
	// Singleton Pattern
	// -----------------------------------------------------------
	static CollisionManager& Get()
	{
		static CollisionManager instance;
		return instance;
	}
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	// -----------------------------------------------------------

	void CheckCollisions();
	void AddBox(const std::shared_ptr<CollisionBox>& box);
	void DeleteBox(const std::shared_ptr<CollisionBox>& box);
	void Init(const std::shared_ptr<Camera>& camera);
	
	
	
	void DrawCBoxes();
	void DebugMode();
	
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	void CollisionManager::updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadBox);

	CollisionGrid _grid;
	std::unordered_map<CollisionGridCase, std::vector<std::shared_ptr<CollisionBox> >> _boxes;
	std::shared_ptr<Camera> _camera;

	// Debug Attributes
	bool _debugMode = false;
};


