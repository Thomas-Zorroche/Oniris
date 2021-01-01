#pragma once 

#include "engine/Camera.hpp"
#include "engine/Terrain.hpp"
#include <iostream>
#include "GLFW/glfw3.h"

class Camera;
class Game;
struct CallbackPtr;

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

	void ProcessInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera, const std::shared_ptr<Game>& game, float deltaTime);
	void SetCallback(GLFWwindow* window, CallbackPtr& callbackPtr);
	ActiveKey GetActiveKey() { return _ActiveKey; };
	
	bool CanInteract() const { return _canInteract; }
	void SetCanInteract(bool interact) { _canInteract = interact; }


private:
	// Prevent using constructors
	InputHandler() = default;
	~InputHandler() = default;

	ActiveKey _ActiveKey = ActiveKey::NONE;
	bool _canInteract = false;

	void Movement(GLFWwindow* window, const std::shared_ptr<Camera>& camera, float deltaTime);
};
//
// callbacks functions
// can't be object function due to glwf syntax
//

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


struct CallbackPtr
{
	std::shared_ptr<Game> _game;
	std::shared_ptr<Camera> _camera;

	CallbackPtr(const std::shared_ptr<Game>& game, const std::shared_ptr<Camera>& camera)
		: _game(game), _camera(camera) {}
};