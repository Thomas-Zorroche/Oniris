#include "engine/InputHandler.hpp"
#include "engine/Camera.hpp"
#include "hud/Hud.hpp"
#include "collision/CollisionManager.hpp"
#include "gameplay/Game.hpp"
#include "engine/AudioManager.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void InputHandler::ProcessInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera, 
    const std::shared_ptr<Game>& game, float deltaTime, CollisionManager& collisionManager)
{
    // Close Window
    // ===================================================================================================
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Sprint 
    // ===================================================================================================
    float boostSprint = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        boostSprint = 2.0f; 

    // Retrive Screen State from Hud
    // ===================================================================================================
    const ScreenState state = Hud::Get().GetState();

    // If player observes a narrative object, he can not move
    // ===================================================================================================
    if (state != ScreenState::OBJMENU && state != ScreenState::MAPMENU)
        Movement(window, camera, deltaTime * boostSprint);

    camera->updateBox();

    // Print Debug cBox Mode
    // ===================================================================================================
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && _ActiveKey != ActiveKey::C) // C Qwerty = C Azerty
    {
        collisionManager.DebugMode();
        _ActiveKey = ActiveKey::C;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE && _ActiveKey == ActiveKey::C)
    {
        _ActiveKey = ActiveKey::NONE;
    }

    // Open map
    // ===================================================================================================
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && _ActiveKey != ActiveKey::A) // Q Qwerty = A Azerty
    {
        if (game->Hasmap())
        {
            if (state == ScreenState::INGAME)
                Hud::Get().SetState(ScreenState::MAPMENU);
            else
                Hud::Get().SetState(ScreenState::INGAME);
        }

        _ActiveKey = ActiveKey::A;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE && _ActiveKey == ActiveKey::A)
    {
        _ActiveKey = ActiveKey::NONE;

    }


    // Observe Narrative Object Panel
    // ===================================================================================================
    if (state == ScreenState::OVERLAP_NO || state == ScreenState::OBJMENU)
    {
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && _ActiveKey != ActiveKey::E)
        {
            _ActiveKey = ActiveKey::E;
            if (state == ScreenState::OBJMENU)
                Hud::Get().SetState(ScreenState::OVERLAP_NO);
            else if ( state == ScreenState::OVERLAP_NO)
                Hud::Get().SetState(ScreenState::OBJMENU);


        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && _ActiveKey == ActiveKey::E)
            _ActiveKey = ActiveKey::NONE;
    }

    // Pick Up Usable Object 
    // ===================================================================================================
    if (state == ScreenState::OVERLAP_UO)
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

void InputHandler::Movement(GLFWwindow* window, const std::shared_ptr<Camera>& camera, float deltaTime) {
    // Movement Inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
    {
        AudioManager::Get().Play("res/audio/footsteps.mp3", 0.4f);
        camera->Move(deltaTime, DIRCAM::FRONT);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)   // S Qwerty = S Azerty
        camera->Move(-deltaTime, DIRCAM::FRONT);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
        camera->Move(deltaTime, DIRCAM::LEFT);
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
        camera->Move(-deltaTime, DIRCAM::LEFT);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
        AudioManager::Get().Stop("res/audio/footsteps.mp3");
}


void InputHandler::SetCallback(GLFWwindow* window, CallbackPtr& callbackPtr)
{
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetWindowUserPointer(window, &callbackPtr);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    CallbackPtr* callbackPtr = (CallbackPtr*)glfwGetWindowUserPointer(window);
    auto camera = callbackPtr->_camera;

    float xoffset = xpos - camera->GetLastX();
    float yoffset = ypos - camera->GetLastY();
    camera->SetLastX(xpos);
    camera->SetLastY(ypos);

    xoffset *= camera->GetSensitivity();
    yoffset *= camera->GetSensitivity();

    if (Hud::Get().GetState() != ScreenState::OBJMENU && Hud::Get().GetState() != ScreenState::MAPMENU)
    {
        camera->rotateLeft(xoffset);
        camera->rotateUp(yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{   
    CallbackPtr* callbackPtr = (CallbackPtr*)glfwGetWindowUserPointer(window);
    auto game = callbackPtr->_game;
    
    if (game->HasKey())
        Hud::Get().Translate("key", game);
    if (game->Hasmap())
        Hud::Get().Translate("map", game);
}