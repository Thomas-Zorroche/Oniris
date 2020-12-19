#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.hpp"
#include "FreeflyCamera.hpp"
#include "Inputs.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "SpecialMesh.hpp"
#include "Terrain.hpp"
#include "Scene.hpp"
#include "CollisionManager.hpp"
#include "InputHandler.hpp"
#include "Game.hpp"


#include <unordered_map> 


void mainloop(GLFWwindow* window)
{
    // Scene Initialization
    Scene scene("worldScene.txt");

    // Camera
    FreeflyCamera camera;
    camera.MoveFront(scene.TerrainPtr(), 1);
    Renderer::Get().SetCamera(&camera);
    Renderer::Get().ComputeProjectionMatrix();

    // Initialisation Collision Manager
    CollisionManager::Get().Init(&camera);

    glEnable(GL_DEPTH_TEST);  

    // Callback
    Game game = Game(&camera, &scene.GetHudPtr());
    InputHandler::Get().SetCallback(window, &game);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Handle Inputs
        InputHandler::Get().ProcessInput(window, camera, scene.TerrainPtr());

        // Check Collisions
        CollisionManager::Get().CheckCollisions();

        // Camera movement according to Inputs
        camera.Move(scene.TerrainPtr());

        // View Matrix
        Renderer::Get().ComputeViewMatrix();
        
        // 84, 199, 195
        glClearColor(0.15f, 0.25f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render scene here
        scene.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
