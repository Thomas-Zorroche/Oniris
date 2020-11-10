#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Sphere.hpp"

#include "FreeflyCamera.hpp"
#include "Inputs.hpp"



void mainloop(GLFWwindow* window)
{
    Sphere sphere(1, 32, 16);
    
    GLuint VAO, VBO, IBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);
    glGenVertexArrays(1, &VAO);

    // 1. Bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * 8 * sizeof(float), sphere.getDataPointer(), GL_STATIC_DRAW);
    // 3. vertex attributes pointers
    glEnableVertexAttribArray(0); // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(1); // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2); // TexCoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(float)));
    // 4. Unbind VAO
    glBindVertexArray(0);

    // Shaders
    Shader shader("res/shaders/Normal3D.shader");

    // Projection Matrix
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    FreeflyCamera camera;

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
        camera.Move();

        /* Render here */
        glClearColor(0.5, 0.15f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Matrices
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 MVP = projection * view;
        glm::mat4 MV = view;
        glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

        // Uniforms
        shader.Bind();
        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "uMVPMatrix"), 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "uMVMatrix"), 1, GL_FALSE, &MV[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "uNormalMatrix"), 1, GL_FALSE, &NormalMatrix[0][0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}
