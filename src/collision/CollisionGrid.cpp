#include "collision/CollisionGrid.hpp"
#include "collision/CollisionBox.hpp"
#include "engine/Camera.hpp"


#include <vector>
#include <memory>


// Return the associate case where the box is currently on
CollisionGridCase CollisionGrid::BoxCase(const std::shared_ptr<CollisionBox>& box)
{
	return CollisionGridCase(box->X() / _widthCase, box->Z() / _widthCase);
}

