#pragma once
#include "engine/Log.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void InitLogLevel(char* level);

class Window
{
public:
    Window(int argc, char** argv);

    void SetWidth(float width) { _width = width; }
    void SetHeight(float height) { height = _height; }

    float Width() const { return _width; }
    float Height() const { return _height; }

    GLFWwindow* WindowPtr() { return _glfw_Window; }

    int Init();

private:
    void HandleArgs(int argc, char** argv);
    void InitScreenSize(char* size);

    float _width = 1280.0f;
    float _height = 720.0f;

    GLFWwindow* _glfw_Window = nullptr;
};


