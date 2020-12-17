#include "InputHandler.hpp"
#include "FreeflyCamera.hpp"
#include <iostream>
#include "GLFW/glfw3.h"


void InputHandler::ProcessInput(GLFWwindow* window, FreeflyCamera& camera,const std::shared_ptr<Terrain> terrain)
{
    /* Close Window */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE
    //    || glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    //{
    //    camera.SetActiveKey('A');
    //}

    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
        camera.MoveFront(terrain, 1);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera.MoveFront(terrain, -1);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera.MoveLeft(terrain, 1);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera.MoveLeft(terrain, -1);
}

void InputHandler::Callback(GLFWwindow* window, FreeflyCamera* camera) {
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowUserPointer(window, camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    FreeflyCamera* camera = (FreeflyCamera*)glfwGetWindowUserPointer(window);
    float xoffset = xpos - camera->GetLastX();
    float yoffset = ypos - camera->GetLastY();
    camera->SetLastX(xpos);
    camera->SetLastY(ypos);

    xoffset *= camera->GetSensitivity();
    yoffset *= camera->GetSensitivity();

    camera->rotateLeft(xoffset);
    camera->rotateUp(yoffset);
}
