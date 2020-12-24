#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Hud.hpp"
#include "CollisionManager.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void InputHandler::ProcessInput(GLFWwindow* window, Camera& camera, float deltaTime)
{
    /* Close Window */
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    ScreenState state = Hud::Get().GetState();
    //std::cout << "State_" << (int)state << std::endl;
    //std::cout << "Key___" << (int)_ActiveKey << std::endl;

    if (state != ScreenState::OBJMENU)
        Movement(window, camera, deltaTime);

    camera.updateBox();

    // Print Debug cBox Mode
    // ===================================================================================================
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && _ActiveKey != ActiveKey::C) // C Qwerty = C Azerty
    {
        CollisionManager::Get().DebugMode();
        _ActiveKey = ActiveKey::C;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE && _ActiveKey == ActiveKey::C)
    {
        _ActiveKey = ActiveKey::NONE;
    }


    // Open Narrative Object Panel
    // ===================================================================================================
    if (Hud::Get().IsVisible("p_observe") || state == ScreenState::OBJMENU)
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E) // C Qwerty = C Azerty
        {
            _ActiveKey = ActiveKey::E;
            if (state == ScreenState::OBJMENU)
                Hud::Get().SetState(ScreenState::INGAME);
            else
                Hud::Get().SetState(ScreenState::OBJMENU);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && _ActiveKey == ActiveKey::E)
            _ActiveKey = ActiveKey::NONE;
    }

    // Pick Up Object 
    // ===================================================================================================
    
    if (Hud::Get().IsVisible("p_pickup"))
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E)
            _ActiveKey = ActiveKey::E;
        
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && _ActiveKey == ActiveKey::E)
            _ActiveKey = ActiveKey::NONE;
    }


    // Interact with IO Object
    // ===================================================================================================
    if (state == ScreenState::OVERLAP_IO)
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E)
        {
            _ActiveKey = ActiveKey::E;
            SetCanInteract(true);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && _ActiveKey == ActiveKey::E)
        {
            _ActiveKey = ActiveKey::NONE;
            SetCanInteract(true);
        }
    }

}

void InputHandler::Movement(GLFWwindow* window, Camera& camera, float deltaTime) {
    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
        camera.MoveFront(deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera.MoveFront(-deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera.MoveLeft(deltaTime);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera.MoveLeft(-deltaTime);
}


void InputHandler::SetCallback(GLFWwindow* window, Camera* camera) 
{
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowUserPointer(window, camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
    float xoffset = xpos - camera->GetLastX();
    float yoffset = ypos - camera->GetLastY();
    camera->SetLastX(xpos);
    camera->SetLastY(ypos);

    xoffset *= camera->GetSensitivity();
    yoffset *= camera->GetSensitivity();

    if (Hud::Get().GetState() != ScreenState::OBJMENU)
    {
        camera->rotateLeft(xoffset);
        camera->rotateUp(yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Hud::Get().Scroll(yoffset);
    std::cout << "scroll   :  " << yoffset << std::endl;
}