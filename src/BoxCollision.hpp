#pragma once

#include "glm/glm.hpp"
#include <memory>

typedef void(*OnBeginOverlapFunction)(void);

class CollisionBox
{
public:
	CollisionBox(const glm::vec3& origin, float w, float h, float d, 
		const OnBeginOverlapFunction& collisionFunction = []{});

	void OnBeginOverlap();
	bool IsColliding(const std::shared_ptr<CollisionBox>& box);

private:
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	float _w = 10.0f, _h = 10.0f, _d = 10.0f;


	OnBeginOverlapFunction _collisionFunction;
};