#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "CollisionManager.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void InputHandler::ProcessInput(GLFWwindow* window, Camera& camera,const std::shared_ptr<Terrain>& terrain)
{
    /* Close Window */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    std::cout << "State_" << (int)_state << std::endl;
    std::cout << "Key___" << (int)_ActiveKey << std::endl;

    switch (_state)
    {
    case ScreenState::INGAME:
        Movement(window, camera, terrain);
        inGameInput(window);
        break;
    case ScreenState::ONOVERLAP:
        Movement(window, camera, terrain);
        OnOverlapInput(window);
        _state = ScreenState::INGAME; //update each frame ; object set _state to onoverlap if needed
        break;
    case ScreenState::OBJMENU:
        ObjMenuInput(window);
        break;
    default:
        break;
    }

    camera.updateBox();
}

void InputHandler::Movement(GLFWwindow* window, Camera& camera, const std::shared_ptr<Terrain>& terrain) {
    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
        camera.MoveFront(1, terrain);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera.MoveFront(-1, terrain);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera.MoveLeft(1, terrain);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera.MoveLeft(-1, terrain);
}
void InputHandler::inGameInput(GLFWwindow* window) {

    // Collision Debug Mode   
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && _ActiveKey != ActiveKey::C) // C Qwerty = C Azerty
    {
        //std::cout << "c pressed \n";

        CollisionManager::Get().DebugMode();
        _ActiveKey = ActiveKey::C;
    }
    else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        //std::cout << "c and released \n";

        _ActiveKey = ActiveKey::NONE;
    }
}

void InputHandler::OnOverlapInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E)   // Q Qwerty = A Azerty
    {
        //std::cout << "e pressed \n";
        _ActiveKey = ActiveKey::E;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        //std::cout << "e realeased \n";
        _ActiveKey = ActiveKey::NONE;
    }
}

void InputHandler::ObjMenuInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && _ActiveKey == ActiveKey::E) {
        std::cout << "e realeased \n";
        _state = ScreenState::INGAME;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E)   // Q Qwerty = A Azerty
    {
        std::cout << "e pressed \n";
        _ActiveKey = ActiveKey::E;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE )
    {
        _ActiveKey = ActiveKey::NONE;
    }

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
    Hud::Get().Scroll(yoffset);
    std::cout << "scroll   :  " << yoffset << std::endl;
}