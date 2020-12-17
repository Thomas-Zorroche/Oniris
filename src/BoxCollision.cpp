#include "BoxCollision.hpp"
#include "glm/glm.hpp"

CollisionBox::CollisionBox(const glm::vec3& origin, float w, float h, float d,
    const OnBeginOverlapFunction& collisionFunction)
	: _x(origin.x), _y(origin.y), _z(origin.z), _w(w), _h(h), _d(d), _collisionFunction(collisionFunction)
{

}

void CollisionBox::OnBeginOverlap()
{
    _collisionFunction();
}

// Check whether the box overlaps with another box
bool CollisionBox::IsColliding(const std::shared_ptr<CollisionBox>& box)
{
    if ((box->_x >= _x + _w)            // trop à droite 
        || (box->_x + box->_w <= _x)    // trop à gauche 
        || (box->_y >= _y + _h)         // trop en bas 
        || (box->_y + box->_h <= _y)    // trop en haut     
        || (box->_z <= _z - _d)         // trop derrière 
        || (box->_z - box->_d >= _z))   // trop devant 
        return false;
    else
        return true;
}

void CollisionBox::AddIndex(CollisionGridCase gridCase, int index)
{
    _indices.insert({ gridCase, index });
}

