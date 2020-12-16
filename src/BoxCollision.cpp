#include "BoxCollision.hpp"

#include <functional>

CollisionBox::CollisionBox(float x, float y, float z, float w, float h, float d,
	const std::function<void(void)>& collisionFunction)
	: _x(x), _y(y), _z(z), _w(w), _h(h), _d(d), _collisionFunction(collisionFunction)
{

}

void CollisionBox::OnBeginOverlap()
{
	_collisionFunction();
}

bool CollisionBox::IsColliding(FreeflyCamera* camera)
{
	return false;
}