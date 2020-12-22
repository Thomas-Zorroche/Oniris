#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "CollisionManager.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void InputHandler::ProcessInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
    /* Close Window */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
        camera.MoveFront(deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera.MoveFront(-deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera.MoveLeft(deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera.MoveLeft(-deltaTime);

    // Collision Debug Mode
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)        // C Qwerty = C Azerty
        CollisionManager::Get().DebugMode();

    camera.updateBox();
}

void InputHandler::SetCallback(GLFWwindow* window, Game* game) {
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowUserPointer(window, game);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = ((Game*)glfwGetWindowUserPointer(window))->camera;
    float xoffset = xpos - camera->GetLastX();
    float yoffset = ypos - camera->GetLastY();
    camera->SetLastX(xpos);
    camera->SetLastY(ypos);

    xoffset *= camera->GetSensitivity();
    yoffset *= camera->GetSensitivity();

    camera->rotateLeft(xoffset);
    camera->rotateUp(yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Hud* hud = ((Game*)glfwGetWindowUserPointer(window))->hud;
    hud->Scroll(int(yoffset));
    std::cout << "scroll   :  " << yoffset << std::endl;
}