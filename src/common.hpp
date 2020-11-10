#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#define M_PI 3.14
#include <cmath>



struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};


