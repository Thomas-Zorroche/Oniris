#pragma once

#include "BaseLight.hpp"
#include <unordered_map>

class PointLight : public BaseLight
{
public:
    PointLight(float intensity = 1.0f,
               const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0),
               const glm::vec3& position = glm::vec3(0, 0, 0),
               float radiusAttenuation = 20.0f);



private:
    // Attenuation variables
    glm::vec3 _position;
    const float _constant = 1.0f;
    float _linear;
    float _quadratic;
    float _radiusAttenuation;

    static const std::unordered_map<int, std::pair<float, float>> _attenuationTable;
};