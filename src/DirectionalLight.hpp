#pragma once

#pragma once

#include "BaseLight.hpp"
#include <unordered_map>

class DirectionalLight : public BaseLight
{
public:
    DirectionalLight(float intensity = 1.0f,
                     const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0),
                     const glm::vec3& direction = glm::vec3(1, 1, 1));

    
    const glm::vec3& Direction() const { return _direction; }
    float SetDirection(const glm::vec3& direction) { _direction = direction; }
    std::vector<glm::vec3> GetSpecialData() override;

private:
    glm::vec3 _direction;
};

