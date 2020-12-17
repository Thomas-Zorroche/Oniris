#pragma once 

#include "FreeflyCamera.hpp"
#include "Terrain.hpp"
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

	void InputHandler::ProcessInput(GLFWwindow* window, FreeflyCamera& camera, const std::shared_ptr<Terrain> terrain);
	void InputHandler::Callback(GLFWwindow* window, FreeflyCamera* camera);

private:
	// Prevent using constructors
	InputHandler() = default;
	~InputHandler() = default;


};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);