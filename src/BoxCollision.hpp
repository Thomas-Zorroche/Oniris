#pragma once

#include <functional>

class FreeflyCamera;

class CollisionBox
{
public:
	CollisionBox(float x, float y, float z, float w, float h, float d, 
				 const std::function<void(void)>& collisionFunction);

	void OnBeginOverlap();
	bool IsColliding(FreeflyCamera* camera);

private:
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	float _w = 10.0f, _h = 10.0f, _d = 10.0f;


	std::function<void(void)> _collisionFunction;
};