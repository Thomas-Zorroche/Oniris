#pragma once

#include "glm/glm.hpp"
#include "CollisionGrid.hpp"
#include <memory>
#include <unordered_map>

typedef void(*OnBeginOverlapFunction)(void);

// All data that define how the cBox will behave
class CollisionLayout
{
public:
	CollisionLayout(bool collision = false, bool stopMovement = false, 
					bool dynamic = false, OnBeginOverlapFunction function = [] {})
		: _hasCollision(collision), _canStopMovement(stopMovement),
		  _dynamicBox(dynamic), _collisionFunction(function) {}

	bool HasCollision() const { return _hasCollision; }
	bool CanStopMovement() const { return _canStopMovement; }
	bool HasDynamicBox() const { return _dynamicBox; }
	OnBeginOverlapFunction Function() const { return _collisionFunction; }

private:
	// Whether cBox has Collision event or not
	bool _hasCollision;

	// Whether cBox can stop movement of the player or not
	bool _canStopMovement;

	// Whether cBox is able to transform (trans, rot and scale)
	bool _dynamicBox;

	// Function called when the player hits the cBox, default is an empty lambda
	OnBeginOverlapFunction _collisionFunction;
};


enum HitCollisionAxis
{
	NONE = 0, X_POS, X_NEG, Y_POS, Y_NEG, Z_POS, Z_NEG
};

// Struct used for collision test
struct HitResult
{
	bool IsHitting;
	HitCollisionAxis axis;
};

class CollisionBox
{
public:
	CollisionBox(const glm::vec3& origin, float w, float h, float d,
		const OnBeginOverlapFunction& collisionFunction = [] {}, bool stopMovement = false);

	void OnBeginOverlap();
	HitResult IsColliding(const std::shared_ptr<CollisionBox>& box);


	float X() const { return _x; }
	float Y() const { return _y; }
	float Z() const { return _z; }

	inline void SetX(float x) { _x = x; }
	inline void SetY(float y) { _y = y; }
	inline void SetZ(float z) { _z = z; }

	const std::unordered_map<CollisionGridCase, int>& Indices() const { return _indices; }
	std::unordered_map<CollisionGridCase, int>& Indices() { return _indices; }
	void AddIndex(CollisionGridCase gridCase, int index);
	void CollisionBox::DecreaseIndexCase(CollisionGridCase gridCase);

private:
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	float _w = 10.0f, _h = 10.0f, _d = 10.0f;

	OnBeginOverlapFunction _collisionFunction;
	std::unordered_map<CollisionGridCase, int> _indices;
	bool _stopMovement = false;
};