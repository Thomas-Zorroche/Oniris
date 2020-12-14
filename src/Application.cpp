#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Renderer.hpp"
#include "Sphere.hpp"
#include "FreeflyCamera.hpp"
#include "Inputs.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "SpecialMesh.hpp"
#include "Terrain.hpp"
#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "Hud.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map> 


void mainloop(GLFWwindow* window)
{
    // Scene Initialization
    Scene scene("worldScene.txt");

    // Camera
    FreeflyCamera camera;
    camera.moveFront(0, scene.TerrainPtr());
    Renderer::Get().SetCamera(&camera);
    Renderer::Get().ComputeProjectionMatrix();

    glEnable(GL_DEPTH_TEST);  

    // Callback function for Mouse Cursor
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowUserPointer(window, &camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Handle Inputs
        processInput(window, camera);

        // Camera movement according to Inputs
        camera.Move(scene.TerrainPtr());

        // View Matrix
        Renderer::Get().ComputeViewMatrix();
        
        glClearColor(0.5, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render scene here
        scene.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
