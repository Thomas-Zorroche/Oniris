#include "Camera.hpp"

Camera::Camera()
	: _Position(512, _HeightCamera, 487), _phi(M_PI), _theta(0), _CanTurn(false),
	_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f),
	_cBox(std::make_shared<CollisionBox>(glm::vec3(_Position), _cBoxWidth, _HeightCamera, _cBoxWidth))
{
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

	switch (_blockAxis)
	{
	case NONE:
		_Position += dir * _FrontVector;
		break;
	case X_POS:
		_Position.z += dir * _FrontVector.z;
		if (dir < 0 || glm::dot(_FrontVector, glm::vec3(1, 0, 0)) < 0)
			_Position.x += dir * _FrontVector.x;
		break;
	case X_NEG:
		_Position.z += dir * _FrontVector.z;
		if (dir < 0 || glm::dot(_FrontVector, glm::vec3(1, 0, 0)) > 0)
			_Position.x += dir * _FrontVector.x;
		break;
	case Z_POS:
		_Position.x += dir * _FrontVector.x;
		if (dir < 0 || glm::dot(_FrontVector, glm::vec3(0, 0, 1)) < 0)
			_Position.z += dir * _FrontVector.z;
		break;
	case Z_NEG:
		_Position.x += dir * _FrontVector.x;
		if (dir < 0 || glm::dot(_FrontVector, glm::vec3(0, 0, 1)) > 0)
			_Position.z += dir * _FrontVector.z;
		break;
	}

	_Position.y = terrain->GetHeightOfTerrain(_Position.x, _Position.z) + _HeightCamera;
	computeDirectionVectors();
}
void Camera::MoveLeft(float t, const std::shared_ptr<Terrain>& terrain)
{
	if (_blockAxis == X_POS || _blockAxis == X_NEG)
		_Position.z += t * _LeftVector.z;
	else if (_blockAxis == Z_POS || _blockAxis == Z_NEG)
		_Position.x += t * _LeftVector.x;
	else
		_Position += t * _LeftVector;

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