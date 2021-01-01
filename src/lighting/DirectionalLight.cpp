#include "lighting/DirectionalLight.hpp"

DirectionalLight::DirectionalLight(float intensity, const glm::vec3& color, const glm::vec3& direction)
    : BaseLight(LightType::DIR, intensity, color), _direction(direction)
{
}

std::vector<glm::vec3> DirectionalLight::GetSpecialData()
{
    return std::vector<glm::vec3>({ _direction });
}
