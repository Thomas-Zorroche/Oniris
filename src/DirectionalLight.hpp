#pragma once

#pragma once

#include "BaseLight.hpp"
#include <unordered_map>

class DirectionalLight : public BaseLight
{
public:
    DirectionalLight(float intensity = 1.0f,
                     const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0),
                     const glm::vec3& direction = glm::vec3(1, 0, 0));



private:
    glm::vec3 _direction;
};