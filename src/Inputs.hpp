#pragma once

#include <GLFW/glfw3.h>
#include "FreeflyCamera.hpp"

void processInput(GLFWwindow* window, FreeflyCamera& camera);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);