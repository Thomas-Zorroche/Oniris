#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/Window.hpp"
#include "engine/Application.hpp"


int main(int argc, char** argv)
{
    Window window(argc, argv);

    /* Initialize the library */
    if (!glfwInit())
        return 0;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* glfw_Window = glfwCreateWindow(window.Width(), window.Height(), "Oniris", NULL, NULL);
    if (!glfw_Window)
    {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(glfw_Window);

    /* Initialize glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    /* Main Game Loop */
    mainloop(glfw_Window);

    glfwTerminate();
    return 0;
}