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

    ShapeVertex::ShapeVertex(glm::vec3 p) :
        position(p), normal(glm::vec3()), texCoords(glm::vec2()) {
    }

    ShapeVertex::ShapeVertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) :
        position(p), normal(n), texCoords(t) {
    }

    ShapeVertex::ShapeVertex() :
        position(glm::vec3(0.0)), normal(glm::vec3(0.0)), texCoords(glm::vec3(0.0)) {
    }
};
