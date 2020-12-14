#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#define M_PI 3.14
#include <cmath>
#include <iostream>

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OPENGL ERROR] " << error << std::endl;
    }
}



struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

};


