/* ======== O N I R I S ========
* OpenGL / C++ Project
* 
* IMAC 2 - Semester 3
* 
* VODABLE Emma, ZORROCHE Thomas
* 
* Using Glad and GLFW
* ==============================
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application.hpp"

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
        return 0;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Oniris", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }
    
    /* Main Game Loop */
    mainloop(window);

    glfwTerminate();
    return 0;
}