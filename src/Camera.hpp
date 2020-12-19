#pragma once

//#define _USE_MATH_DEFINES
#define M_PI 3.14
#include <cmath>
#include <iostream>
#include <algorithm>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Terrain.hpp"
#include "CollisionBox.hpp"

#define NOMINAX // Avoid conflicts between min and max constants in Windef.h

class Camera
{
public:
	Camera();
	~Camera() {}

	void updateBox();

	void MoveFront(float dir, const std::shared_ptr<Terrain>& terrain);
	void MoveLeft(float t, const std::shared_ptr<Terrain>& terrain);

	void rotateUp(float angle);
	void rotateLeft(float angle);


	// Getters Camera Data
	float GetFov() const { return _fov; }
	float GetWidth() const { return _widthScreen; }
	float GetHeight() const { return _heightScreen; }
	float GetNearPlane() const { return _nearPlane; }
	float GetFarPlane() const { return _farPlane; }
	inline glm::mat4 getViewMatrix() const 	{ return glm::lookAt(_Position, _Position + _FrontVector, _UpVector); }
	// Getters Camera Gameplay
	bool GetCanTurn() const  { return _CanTurn; }
	float GetLastX() const  { return _lastX; }
	float GetLastY() const  { return _lastY; }
	float GetSensitivity() const  { return _sensitivity; }
	char GetActiveKey() const  { return _ActiveKey; };
	float GetSpeed() const  { return _Speed; };
	// Getters Collision Data
	std::shared_ptr<CollisionBox> GetCollisionBox() { return _cBox; }
	inline HitCollisionAxis BlockAxis() const { return _blockAxis; }
	
	// Setters
	void SetCanTurn(bool condition) { _CanTurn = condition; }
	void SetLastX(float x) { _lastX = x; }
	void SetLastY(float y) { _lastY = y; }
	virtual void SetActiveKey(char key) { _ActiveKey = key; };
	void BlockMovement(HitCollisionAxis axis) { _blockAxis = axis; }


private:
	void computeDirectionVectors();

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
	float _cBoxWidth = 2.0f;
	std::shared_ptr<CollisionBox> _cBox;
	HitCollisionAxis _blockAxis = NONE;
};
