#pragma once

//#define _USE_MATH_DEFINES
#define M_PI 3.14
#include <cmath>
#include <iostream>
#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Terrain.hpp"
#include "BoxCollision.hpp"

#define NOMINAX // Avoid conflicts between min and max constants in Windef.h

class FreeflyCamera
{
private:
	glm::vec3 _Position;	  // Position of the camera
	float _phi;
	float _theta;
	
	glm::vec3 _FrontVector;   // Direction
	glm::vec3 _LeftVector;    // Left
	glm::vec3 _UpVector;      // Up

	bool _CanTurn;    // Is Able to Turn ?
	float _lastX;     // Last Mouse coordinates
	float _lastY;

	// Input Data
	float _sensitivity;
	char _ActiveKey = 'A';
	float _Speed = 1.5f;
	float _HeightCamera = 15.0f;

	// Technical Data
	float _fov = 45.0f;
	float _widthScreen = 1280.0f;
	float _heightScreen = 720.0f;
	float _nearPlane = 0.1f;
	float _farPlane = 5000.0f;

	// Box Collision
	float _cBoxWidth = 5.0f;
	std::shared_ptr<CollisionBox> _cBox;
	HitCollisionAxis _blockAxis = NONE;

public:
	FreeflyCamera()
		: _Position(512, _HeightCamera, 487), _phi(M_PI), _theta(0), _CanTurn(false),
		_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f), 
		_cBox(std::make_shared<CollisionBox>(glm::vec3(_Position), _cBoxWidth, _HeightCamera, _cBoxWidth))
	{
		computeDirectionVectors();
	}

	~FreeflyCamera() {}

	float GetFov() const { return _fov; }
	float GetWidth() const { return _widthScreen; }
	float GetHeight() const { return _heightScreen; }
	float GetNearPlane() const { return _nearPlane; }
	float GetFarPlane() const { return _farPlane; }

private:
	void computeDirectionVectors()
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

	void updateBox()
	{
		_cBox->SetX(_Position.x - (_cBoxWidth / 2.0));
		_cBox->SetY(_Position.y - _HeightCamera);
		_cBox->SetZ(_Position.z + (_cBoxWidth / 2.0));
	}


public:
	void Move(const std::shared_ptr<Terrain>& terrain)
	{

		switch (_ActiveKey)
		{
		case 'Z':
			moveFront(_Speed, terrain);
			break;
		case 'Q':
			moveLeft(_Speed, terrain);
			break;
		case 'S':
			moveFront(-_Speed, terrain);
			break;
		case 'D':
			moveLeft(-_Speed, terrain);
			break;
		case 'A':
			break;
		}

		updateBox();
	}

	void moveFront(float dir, const std::shared_ptr<Terrain>& terrain)
	{ 
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
	void moveLeft(float t, const std::shared_ptr<Terrain>& terrain)
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

	void rotateUp(float angle)  
	{ 
		_theta -= glm::radians(angle); 
		computeDirectionVectors();
	}
	void rotateLeft(float angle)  
	{ 
		_phi -= glm::radians(angle); 
		computeDirectionVectors();
	}

	glm::mat4 getViewMatrix() const 
	{
		return glm::lookAt(_Position, _Position + _FrontVector, _UpVector);
	}

	// Getters
	bool GetCanTurn() const  { return _CanTurn; }
	float GetLastX() const  { return _lastX; }
	float GetLastY() const  { return _lastY; }
	float GetSensitivity() const  { return _sensitivity; }
	char GetActiveKey() const  { return _ActiveKey; };
	float GetSpeed() const  { return _Speed; };
	std::shared_ptr<CollisionBox> GetCollisionBox() { return _cBox; }
	inline HitCollisionAxis BlockAxis() const { return _blockAxis; }
	
	// Setters
	void SetCanTurn(bool condition) { _CanTurn = condition; }
	void SetLastX(float x) { _lastX = x; }
	void SetLastY(float y) { _lastY = y; }
	virtual void SetActiveKey(char key) { _ActiveKey = key; };

	void BlockMovement(HitCollisionAxis axis) { _blockAxis = axis; }
};
