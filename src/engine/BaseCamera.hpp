#pragma once

#include "glm/glm.hpp"


class BaseCamera
{
public:
	virtual void moveFront(float delta) = 0;
	virtual void moveLeft(float delta) {}

	virtual void rotateLeft(float angle) = 0;
	virtual void rotateUp(float angle) = 0;

	virtual glm::mat4 getViewMatrix() const = 0;

	// Getters
	virtual bool GetCanTurn() const = 0;
	virtual float GetLastX() const = 0;
	virtual float GetLastY() const = 0;
	virtual float GetSensitivity() const = 0;
	virtual char GetActiveKey() const { return _ActiveKey; };
	virtual float GetSpeed() const { return _Speed; };

	// Setters
	virtual void SetCanTurn(bool condition) = 0;
	virtual void SetLastX(float x) = 0;
	virtual void SetLastY(float y) = 0;
	virtual void SetActiveKey(char key) {};

protected:
	char _ActiveKey = 'A';
	float _Speed = 0.05f;
};