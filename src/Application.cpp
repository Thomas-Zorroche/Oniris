#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "StaticMesh.hpp"
#include "Terrain.hpp"
#include "Scene.hpp"
#include "CollisionManager.hpp"
#include "InputHandler.hpp"
#include "Hud.hpp"
#include "ShapeCube.hpp"

#include "irrKlang/irrKlang.h"


#include <unordered_map> 


void mainloop(GLFWwindow* window)
{
    // Sound engine 
    irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
    SoundEngine->play2D("res/audio/musicbox.mp3", true);

    // Scene Initialization
    Scene scene("worldScene.txt");

    // Camera
    Camera camera(scene.TerrainPtr());
    Renderer::Get().SetCamera(&camera);
    Renderer::Get().ComputeProjectionMatrix();

    // Initialisation Collision Manager
    CollisionManager::Get().Init(&camera);

    glEnable(GL_DEPTH_TEST);  

    // Initialize GLFW Callbacks
    InputHandler::Get().SetCallback(window, &camera);

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // Handle Inputs
        InputHandler::Get().ProcessInput(window, camera, deltaTime);

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