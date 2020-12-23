#pragma once 

#include "Camera.hpp"
#include "Terrain.hpp"
#include <iostream>
#include "GLFW/glfw3.h"

enum class ActiveKey {
	NONE, 
	C,	// show cBOx
	E,	// enter menu
	A	// use object
};

class InputHandler
{
public:
	// Static method to get the only instance shared by the class
	static InputHandler& Get()
	{
		static InputHandler instance;
		return instance;
	}

	// Delete copy constructor and = operator
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;

	void InputHandler::ProcessInput(GLFWwindow* window, Camera& camera, const std::shared_ptr<Terrain>& terrain);
	void InputHandler::SetCallback(GLFWwindow* window, Camera* camera);
	ActiveKey InputHandler::GetActiveKey() { return _ActiveKey; };


private:
	// Prevent using constructors
	InputHandler() = default;
	~InputHandler() = default;

	ActiveKey _ActiveKey = ActiveKey::NONE;

	void Movement(GLFWwindow* window, Camera& camera, const std::shared_ptr<Terrain>& terrain);
};
//
// callbacks functions
// can't be object function due to glwf syntax
//

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
