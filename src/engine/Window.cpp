#include "engine/Window.hpp"

#include <iostream>
#include <string.h> 

Window::Window(int argc, char** argv)
{
    HandleArgs(argc, argv);
    
}

int Window::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return 0;

    /* Create a windowed mode window and its OpenGL context */
    _glfw_Window = glfwCreateWindow(_width, _height, "Oniris", NULL, NULL);
    if (!_glfw_Window)
    {
        glfwTerminate();
        return 0;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_glfw_Window);

    /* Initialize glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 0;
    }

    return 1;
}

/*
* ===============================================================
* Private Functions
* ===============================================================
*/
void Window::HandleArgs(int argc, char** argv)
{
    std::string none = "-none";
    std::string hd = "-hd";

    char cstrNONE[none.size() + 1];
    char cstrHD[hd.size() + 1];
    strcpy(cstrNONE, none.c_str());
    strcpy(cstrHD, hd.c_str());
 
    InitLogLevel(cstrNONE);
    InitScreenSize(cstrHD);

    for (size_t i = 1; i < (size_t)argc; i++)
    {
        if (strcmp(argv[i], "-none") == 0 || strcmp(argv[i], "-info") == 0 || strcmp(argv[i], "-warning") == 0)
            InitLogLevel(argv[i]);
        else if (strcmp(argv[i], "-hd") == 0 || strcmp(argv[i], "-fhd") == 0)
            InitScreenSize(argv[i]);
    }
}

void Window::InitScreenSize(char* size)
{
    if (strcmp(size, "-hd") == 0)
    {
        _width = 1280.0f;
        _height = 720.0f;
    }
    else if (strcmp(size, "-fhd") == 0)
    {
        _width = 1920.0f;
        _height = 1080.0f;
    }
}

/*
* ===============================================================
* Utility Functions
* ===============================================================
*/
void InitLogLevel(char* level)
{
    if (strcmp(level, "-info") == 0)
        Log::Get().SetLevel(LogLevel::INFO);
    else if (strcmp(level, "-warning") == 0)
        Log::Get().SetLevel(LogLevel::WARNING);
    else if (strcmp(level, "-error") == 0)
        Log::Get().SetLevel(LogLevel::ERROR);
    else
        Log::Get().SetLevel(LogLevel::NONE);
}