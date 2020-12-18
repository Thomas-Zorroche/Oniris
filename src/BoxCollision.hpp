#pragma once

#include "glm/glm.hpp"
#include "CollisionGrid.hpp"
#include <memory>
#include <unordered_map>

typedef void(*OnBeginOverlapFunction)(void);

enum HitCollisionAxis
{
	NONE = 0, X_POS, X_NEG, Y_POS, Y_NEG, Z_POS, Z_NEG
};

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

private:
	float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	float _w = 10.0f, _h = 10.0f, _d = 10.0f;

	OnBeginOverlapFunction _collisionFunction;
	std::unordered_map<CollisionGridCase, int> _indices;
	bool _stopMovement = false;
};