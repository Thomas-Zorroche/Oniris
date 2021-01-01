#include "engine/Camera.hpp"
#include "engine/Terrain.hpp"

float Lerp(float start, float end, float t);

Camera::Camera(const std::shared_ptr<Terrain>& terrain)
	: _terrain(terrain), 
	_Position(499, _terrain->GetHeightOfTerrain(499, 600) + _HeightCamera, 600), _phi(M_PI), _theta(0), _CanTurn(false),
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

void Camera::Move(float deltaTime, DIRCAM direction)
{
	glm::vec3 dir;
	(direction == DIRCAM::FRONT) ? dir = _FrontVector : dir = _LeftVector;
		
	float dirX = glm::dot(dir, glm::vec3(1, 0, 0));
	float dirZ = glm::dot(dir, glm::vec3(0, 0, 1));

	float dst = deltaTime * _Speed;

	// None of the axis are blocked
	if (_blockAxis[NONE])
	{
		MoveX(dst, dir);
		MoveZ(dst, dir);
	}
	// Just one axis is blocked
	else if (_blockAxis[X_POS] && (!_blockAxis[Z_NEG] && !_blockAxis[Z_POS]))
	{
		MoveZ(dst, dir);
		if (dst < 0 || dirX < 0)
			MoveX(dst, dir);
	}
	else if (_blockAxis[X_NEG] && (!_blockAxis[Z_NEG] && !_blockAxis[Z_POS]))
	{
		MoveZ(dst, dir);
		if (dst < 0 || dirX > 0)
			MoveX(dst, dir);
	}
	else if (_blockAxis[Z_POS] && (!_blockAxis[X_NEG] && !_blockAxis[X_POS]))
	{
		MoveX(dst, dir);
		if (dst < 0 || dirZ < 0)
			MoveZ(dst, dir);
	}
	else if (_blockAxis[Z_NEG] && (!_blockAxis[X_NEG] && !_blockAxis[X_POS]))
	{
		MoveX(dst, dir);
		if (dst < 0 || dirZ > 0)
			MoveZ(dst, dir);
	}
	// Two axis are blocked
	else if (_blockAxis[X_POS] && _blockAxis[Z_POS])
	{
		if (dst < 0 || dirX < 0)
			MoveX(dst, dir);
		if (dst < 0 || dirZ < 0)
			MoveZ(dst, dir);
	}
	else if (_blockAxis[X_POS] && _blockAxis[Z_NEG])
	{
		if (dst < 0 || dirX < 0)
			MoveX(dst, dir);
		if (dst < 0 || dirZ > 0)
			MoveZ(dst, dir);
	}
	else if (_blockAxis[X_NEG] && _blockAxis[Z_POS])
	{
		if (dst < 0 || dirX > 0)
			MoveX(dst, dir);
		if (dst < 0 || dirZ < 0)
			MoveZ(dst, dir);
	}
	else if (_blockAxis[X_NEG] && _blockAxis[Z_NEG])
	{
		if (dst < 0 || dirX > 0)
			MoveX(dst, dir);
		if (dst < 0 || dirZ > 0)
			MoveZ(dst, dir);
	}

	_Position.y = Lerp(_Position.y, _terrain->GetHeightOfTerrain(_Position.x, _Position.z) +_HeightCamera, abs(deltaTime) * _responsiveness);
	_Position.y = glm::clamp(_Position.y, 12.0f, 100.0f);

	_cameraTime += abs(deltaTime);
	float offset_factor = sin(_cameraTime * _frequenceShake) * _amplitudeShake;

	rotateUp(offset_factor);
	
	computeDirectionVectors();

	//std::cout << _Position.x << " " << _Position.z << std::endl;
	//std::cout << _Position.y << std::endl;
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

void Camera::MoveX(float dst, const glm::vec3& dir)
{
	_Position.x += dst * dir.x;
	if (CheckNormal() || _Position.x < 0.0f || _Position.x > 1024.0f)
		_Position.x -= dst * dir.x;
}

void Camera::MoveZ(float dst, const glm::vec3& dir)
{
	_Position.z += dst * dir.z;
	if (CheckNormal() || _Position.z < 0.0f || _Position.z > 1024.0f)
		_Position.z -= dst * dir.z;
}

bool Camera::CheckNormal()
{
	// Check whether normal is under the limit
	glm::vec3 normal = _terrain->GetNormal(_Position.x, _Position.z);
	if (abs(normal.x) > _limitNormal || abs(normal.z) > _limitNormal)
		return true;
	return false;
}


float Lerp(float start, float end, float t)
{
	return start * (1 - t) + end * t;
}
