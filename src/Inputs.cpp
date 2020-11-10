#include "Inputs.hpp"

#include <GLFW/glfw3.h>
#include "FreeflyCamera.hpp"

#include <iostream>

void processInput(GLFWwindow* window, FreeflyCamera& camera)
{
    /* Close Window */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE
        || glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        camera.SetActiveKey('A');
    }

    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
        camera.SetActiveKey('Z');
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera.SetActiveKey('S');
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera.SetActiveKey('Q');
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera.SetActiveKey('D');
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

