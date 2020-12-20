#include "Camera.hpp"

Camera::Camera()
	: _Position(512, _HeightCamera, 487), _phi(M_PI), _theta(0), _CanTurn(false),
	_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f),
	_cBox(std::make_shared<CollisionBox>(glm::vec3(_Position), _cBoxWidth, _HeightCamera, _cBoxWidth))
{
	_blockAxis[NONE] = true;
	computeDirectionVectors();
}

void Camera::updateBox()
{
	_cBox->SetX(_Position.x - (_cBoxWidth / 2.0));
	_cBox->SetY(_Position.y - _HeightCamera);
	_cBox->SetZ(_Position.z + (_cBoxWidth / 2.0));
}

void Camera::MoveFront(float dir, const std::shared_ptr<Terrain>& terrain)
{
	dir *= _Speed;
	float dirX = glm::dot(_FrontVector, glm::vec3(1, 0, 0));
	float dirZ = glm::dot(_FrontVector, glm::vec3(0, 0, 1));

	// None of the axis are blocked
	if (_blockAxis[NONE])
		_Position += dir * _FrontVector;
	// Just one axis is blocked
	else if (_blockAxis[X_POS] && (!_blockAxis[Z_NEG] && !_blockAxis[Z_POS]))
	{
		_Position.z += dir * _FrontVector.z;
		if (dir < 0 || dirX < 0)
			_Position.x += dir * _FrontVector.x;
	}
	else if (_blockAxis[X_NEG] && (!_blockAxis[Z_NEG] && !_blockAxis[Z_POS]))
	{
		_Position.z += dir * _FrontVector.z;
		if (dir < 0 || dirX > 0)
			_Position.x += dir * _FrontVector.x;
	}
	else if (_blockAxis[Z_POS] && (!_blockAxis[X_NEG] && !_blockAxis[X_POS]))
	{
		_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ < 0)
			_Position.z += dir * _FrontVector.z;
	}
	else if (_blockAxis[Z_NEG] && (!_blockAxis[X_NEG] && !_blockAxis[X_POS]))
	{
		_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ > 0)
			_Position.z += dir * _FrontVector.z;
	}
	// Two axis are blocked
	else if (_blockAxis[X_POS] && _blockAxis[Z_POS])
	{
		if (dir < 0 || dirX < 0)
			_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ < 0)
			_Position.z += dir * _FrontVector.z;
	}
	else if (_blockAxis[X_POS] && _blockAxis[Z_NEG])
	{
		if (dir < 0 || dirX < 0)
			_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ > 0)
			_Position.z += dir * _FrontVector.z;
	}
	else if (_blockAxis[X_NEG] && _blockAxis[Z_POS])
	{
		if (dir < 0 || dirX > 0)
			_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ < 0)
			_Position.z += dir * _FrontVector.z;
	}
	else if (_blockAxis[X_NEG] && _blockAxis[Z_NEG])
	{
		if (dir < 0 || dirX > 0)
			_Position.x += dir * _FrontVector.x;
		if (dir < 0 || dirZ > 0)
			_Position.z += dir * _FrontVector.z;
	}

	_Position.y = terrain->GetHeightOfTerrain(_Position.x, _Position.z) + _HeightCamera;
	computeDirectionVectors();

	std::cout << _Position.x << " " << _Position.z << std::endl;
}
void Camera::MoveLeft(float dir, const std::shared_ptr<Terrain>& terrain)
{
	dir *= _Speed;
	for (auto axis : _blockAxis)
	{
		if (axis == X_POS || axis == X_NEG)
			_Position.z += dir * _LeftVector.z;
		else if (axis == Z_POS || axis == Z_NEG)
			_Position.x += dir * _LeftVector.x;
		else
			_Position += dir * _LeftVector;
	}

	_Position.y = terrain->GetHeightOfTerrain(_Position.x, _Position.z) + _HeightCamera;
	computeDirectionVectors();
}

void Camera::rotateUp(float angle)
{
	_theta -= glm::radians(angle);
	computeDirectionVectors();
}
void Camera::rotateLeft(float angle)
{
	_phi -= glm::radians(angle);
	computeDirectionVectors();
}

/*
* Collision
*/
void Camera::BlockMovement(const std::vector<HitCollisionAxis>& Axis)
{ 
	// Reset all axis to false
	for (size_t i = 0; i < 5; i++)
		_blockAxis[i] = false;

	for (auto axis : Axis)
		_blockAxis[axis] = true;
}

/*
* Private Functions
*/
void Camera::computeDirectionVectors()
{
	// Direction
	_FrontVector = glm::vec3(glm::cos(glm::radians(_theta)) * glm::sin(glm::radians(_phi)),
		glm::sin(glm::radians(_theta)),
		glm::cos(glm::radians(_theta)) * glm::cos(glm::radians(_phi)));

	// Left
	_LeftVector = glm::vec3((glm::sin(glm::radians(_phi) + (M_PI / 2))),
		0,
		glm::cos(glm::radians(_phi) + (M_PI / 2)));
	// Up
	_UpVector = glm::cross(_FrontVector, _LeftVector);
}