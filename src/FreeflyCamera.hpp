#pragma once

//#define _USE_MATH_DEFINES
#define M_PI 3.14
#include <cmath>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Terrain.hpp"

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
	float _Speed = 3.0f;
	float _HeightCamera = 10.0f;

	// Technical Data
	float _fov = 45.0f;
	float _widthScreen = 1280.0f;
	float _heightScreen = 720.0f;
	float _nearPlane = 0.1f;
	float _farPlane = 1000.0f;

public:
	FreeflyCamera()
		: _Position(10, 1, 10), _phi(M_PI), _theta(0), _CanTurn(false),
		_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f) 
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

public:
	void Move(const std::shared_ptr<Terrain>& terrain)
	{
		switch (_ActiveKey)
		{
		case 'Z':
			moveFront(_Speed, terrain);
			break;
		case 'Q':
			moveLeft(_Speed);
			break;
		case 'S':
			moveFront(-_Speed, terrain);
			break;
		case 'D':
			moveLeft(-_Speed);
			break;
		case 'A':
			break;
		}
	}

	void moveFront(float t, const std::shared_ptr<Terrain>& terrain)
	{ 
		_Position += t * _FrontVector; 
		_Position.y = terrain->GetHeightOfTerrain(_Position.x, _Position.z) + _HeightCamera;
		computeDirectionVectors();
	}
	void moveLeft(float t)  
	{ 
		_Position += t * _LeftVector; 
		_Position.y = 1.0f;
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
	
	// Setters
	void SetCanTurn(bool condition) { _CanTurn = condition; }
	void SetLastX(float x) { _lastX = x; }
	void SetLastY(float y) { _lastY = y; }
	virtual void SetActiveKey(char key) { _ActiveKey = key; };
};
