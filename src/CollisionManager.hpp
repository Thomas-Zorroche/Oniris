#pragma once

#include "CollisionBox.hpp"
#include "CollisionGrid.hpp"
#include "CollisionGrid.hpp"

#include "Camera.hpp"

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
	void Init(Camera* camera);
	
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	void CollisionManager::updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadBox);

	CollisionGrid _grid;
	std::unordered_map<CollisionGridCase, std::vector<std::shared_ptr<CollisionBox> >> _boxes;
	Camera * _camera;
	int _countCollision = 0;
};


