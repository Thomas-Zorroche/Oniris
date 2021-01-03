#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include <iostream>


template<typename T>
T Lerp(T start, T end, T t)
{
    return start * (1 - t) + end * t;
}

struct ShapeVertex 
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    template<typename T>
    ShapeVertex(T x, T y, T z)
        : position(glm::vec3(x, y, z)), normal(glm::vec3()), texCoords(glm::vec2()) {}

    ShapeVertex(glm::vec3 p) 
        : position(p), normal(glm::vec3()), texCoords(glm::vec2()) {}

    ShapeVertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) 
        : position(p), normal(n), texCoords(t) {}

    ShapeVertex() 
        : position(glm::vec3(0.0)), normal(glm::vec3(0.0)), texCoords(glm::vec3(0.0)) {}
};




