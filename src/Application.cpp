#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Sphere.hpp"
#include "FreeflyCamera.hpp"
#include "Inputs.hpp"
#include "Mesh.hpp"
#include "Terrain.hpp"


void mainloop(GLFWwindow* window)
{
    // Sphere
    Sphere sphere(1, 32, 16);
    Mesh   m_sphere(sphere.getVertices());
    Shader s_Normal("res/shaders/Normal3D.shader");

    // Terrain
    Texture t_grass("res/img/grass_diffuse.jpg", "texture_diffuse");
    Texture t_heightmap("res/img/heightmap.png", "texture_heightmap");
    Terrain terrain(0, 0, t_grass, t_heightmap);
    Shader  s_grass("res/shaders/GrassTex.shader");

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 500.0f);
    FreeflyCamera camera;
    camera.moveFront(0, terrain);

    glEnable(GL_DEPTH_TEST);

    // Callback function for Mouse Cursor
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowUserPointer(window, &camera);

    // Hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Handle Inputs
        processInput(window, camera);

        // Camera movement according to Inputs
        camera.Move(terrain);

        /* Render here */
        glClearColor(0.5, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 MVP = projection * view;
        glm::mat4 MV = view;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

        // Uniforms
        // Blinn-Phong
        s_grass.Bind();
        glm::mat4 modelLight = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 0), glm::vec3(0, 1, 0));
        glm::vec4 LightDirection = view * modelLight * glm::vec4(1, 1, 1, 0);
        glUniform3f(glGetUniformLocation(s_grass.getID(), "u_LightDir_vs"), LightDirection.x, LightDirection.y, LightDirection.z);
        glUniform3f(glGetUniformLocation(s_grass.getID(), "u_LightIntensity"), 1.0, 1.0, 1.0);
        glUniform1f(glGetUniformLocation(s_grass.getID(), "u_Shininess"), 16.0);
        // Coeff de reflection diffuse
        glUniform3f(glGetUniformLocation(s_grass.getID(), "u_Kd"), 1.0, 1.0, 1.0);
        // Coeff de reflection glossy
        glUniform3f(glGetUniformLocation(s_grass.getID(), "u_Ks"), 1.0, 1.0, 1.0);

        // Normal Shader
        s_Normal.Bind();
        glUniformMatrix4fv(glGetUniformLocation(s_Normal.getID(), "uMVPMatrix"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(s_Normal.getID(), "uMVMatrix"), 1, GL_FALSE, &MV[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(s_Normal.getID(), "uNormalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

        // Grass Shader
        s_grass.Bind();
        glUniformMatrix4fv(glGetUniformLocation(s_grass.getID(), "uMVPMatrix"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(s_grass.getID(), "uMVMatrix"), 1, GL_FALSE, &MV[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(s_grass.getID(), "uNormalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

        // Draw Functions
        m_sphere.Draw(s_Normal);
        terrain.getMesh().Draw(s_grass);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
