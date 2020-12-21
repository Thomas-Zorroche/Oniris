#pragma once 

#include "Camera.hpp"
#include "Terrain.hpp"
#include "Game.hpp"
#include <iostream>
#include "GLFW/glfw3.h"

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

	void InputHandler::ProcessInput(GLFWwindow* window, Camera& camera, float deltaTime);
	void InputHandler::SetCallback(GLFWwindow* window, Game* game);

private:
	// Prevent using constructors
	InputHandler() = default;
	~InputHandler() = default;


};
//
// callbacks functions
// can't be object function due to glwf syntax
//

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
