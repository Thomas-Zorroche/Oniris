#include "CollisionGrid.hpp"
#include "BoxCollision.hpp"
#include "FreeflyCamera.hpp"


#include <vector>
#include <memory>



CollisionGridCase CollisionGrid::BoxCase(const std::shared_ptr<CollisionBox>& box)
{
	return CollisionGridCase(0, 0);
}

