#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(float intensity = 1.0f,
    const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0),
    const glm::vec3& direction = glm::vec3(1, 0, 0))
    : BaseLight(intensity, color), _direction(direction)
{

}