#include "CollisionGrid.hpp"
#include "BoxCollision.hpp"
#include "FreeflyCamera.hpp"


#include <vector>
#include <memory>


// Return the associate case where the box is currently on
CollisionGridCase CollisionGrid::BoxCase(const std::shared_ptr<CollisionBox>& box)
{
	return CollisionGridCase(box->X() / _widthCase, box->Z() / _widthCase);
}

