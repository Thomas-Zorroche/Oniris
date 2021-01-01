#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "CollisionManager.hpp"
#include "InputHandler.hpp"
#include "Hud.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"


void mainloop(GLFWwindow* window)
{
    // Game
    ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/portal.frag", "Portal");
    auto game = std::make_shared<Game>();

    // Scene Initialization
    Scene scene("worldScene.txt", game);

    // Camera
    auto camera = std::make_shared<Camera>(scene.TerrainPtr());
    Renderer::Get().SetCamera(camera);
    Renderer::Get().ComputeProjectionMatrix();

    // Sound
    AudioManager::Get().Init();

    // Initialisation Collision Manager
    CollisionManager::Get().Init(camera);

    glEnable(GL_DEPTH_TEST);  

    // Initialize GLFW Callbacks
    InputHandler::Get().SetCallback(window, CallbackPtr(game, camera));

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Update sound
        AudioManager::Get().SetListenerPosition(camera->GetPosition(), camera->GetFrontVector());

        // Handle Inputs
        InputHandler::Get().ProcessInput(window, camera, game, deltaTime);

        // View Matrix
        Renderer::Get().ComputeViewMatrix();

        //Hud update
        Hud::Get().Update();
        
        // 84, 199, 195
        glClearColor(0.15f, 0.25f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Check Collisions
        CollisionManager::Get().CheckCollisions();

        // Render scene here
        scene.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}