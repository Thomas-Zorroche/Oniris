#include "engine/Application.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"
#include "engine/Scene.hpp"
#include "engine/InputHandler.hpp"
#include "engine/AudioManager.hpp"
#include "engine/ResourceManager.hpp"

#include "gameplay/Game.hpp"

#include "collision/CollisionManager.hpp"

#include "hud/Hud.hpp"


void mainloop(GLFWwindow* window)
{
    // Load all the shaders
    ResourceManager::Get().LoadAllShaders();

    // Game
    std::shared_ptr<Game> game = std::make_shared<Game>();

    // Scene Initialization
    Scene scene("worldScene.txt", game);

    // Camera
    auto camera = std::make_shared<Camera>(scene.TerrainPtr());
    Renderer::Get().SetCamera(camera);

    // Sound 
    //========================================================    
    AudioManager::Get().Play("res/audio/music.mp3", 0.005f);
    AudioManager::Get().Play("res/audio/forest.mp3", 0.02f);
    AudioManager::Get().SetUpSea();
    AudioManager::Get().SetUpRiver();
    AudioManager::Get().PlayWind();

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