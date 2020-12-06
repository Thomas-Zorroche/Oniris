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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map> 


void mainloop(GLFWwindow* window)
{
    // Scene Initialization
    Scene scene("worldScene.txt");

    // Terrain
    std::shared_ptr<Shader> sh_Terrain = ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
    Terrain terrain(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap16.png");

    
    // Static Mesh
    std::shared_ptr<Shader> sh_Portail = ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");
    Model m_portail("res/models/portail/portail.obj");
    StaticMesh sm_portail(m_portail, glm::vec3(250, terrain.GetHeightOfTerrain(250, 250), 250), "Portail");

    // Camera
    FreeflyCamera camera;
    camera.moveFront(0, terrain);

    // Renderer
    std::vector<StaticMesh *> StaticMeshes = { &sm_portail };
    Renderer renderer(&camera, StaticMeshes, &terrain);

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
        camera.Move(terrain);

        // View Matrix
        renderer.ComputeViewMatrix();
        
        glClearColor(0.5, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render all the Static Meshes and the Terrain
        // ============================================
        renderer.DrawScene();
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
