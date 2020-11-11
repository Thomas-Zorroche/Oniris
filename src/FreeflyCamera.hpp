#pragma once

//#define _USE_MATH_DEFINES
#define M_PI 3.14
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


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
	float _sensitivity;

	char _ActiveKey = 'A';
	float _Speed = 0.05f;

public:
	FreeflyCamera()
		: _Position(5, 1, 5), _phi(M_PI), _theta(0), _CanTurn(false),
		_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f) 
	{
		computeDirectionVectors();
	}

	~FreeflyCamera() {}

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
	void Move()
	{
		switch (_ActiveKey)
		{
		case 'Z':
			moveFront(_Speed);
			break;
		case 'Q':
			moveLeft(_Speed);
			break;
		case 'S':
			moveFront(-_Speed);
			break;
		case 'D':
			moveLeft(-_Speed);
			break;
		case 'A':
			break;
		}
	}

	void moveFront(float t)	 
	{ 
		_Position += t * _FrontVector; 
		_Position.y = 1.0f;
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
