#include "PointLight.hpp"

PointLight::PointLight(float intensity,
                       const glm::vec3& color,
                       const glm::vec3& position,
                       float radius,
                       bool electricity)
    : BaseLight(LightType::POINT, intensity, color, electricity), _position(position), _radius(radius)
{
    UpdateAttenuation();
}

void PointLight::UpdateAttenuation()
{
    auto it = _attenuationTable.find(_radius);
    if (it == _attenuationTable.end())
    {
        throw std::string("Wrong radius size, be sure to check the table in PointLight.cpp and choose an available radius.");
        // Default point light attenuation values
        _radius = 20.0;
        _linear = 0.22;
        _quadratic = 0.2;
    }
    else
    {
        _linear = it->second.first;
        _quadratic = it->second.second;
    }
}

void PointLight::SetRadius(const float radius)
{
    _radius = radius;
    UpdateAttenuation();
}

std::vector<glm::vec3> PointLight::GetSpecialData()
{
    return std::vector<glm::vec3>({_position, glm::vec3(1.0f, _linear, _quadratic)});
}


/*
* Attenuation values per radius
* 
* radius  |  Linear  |  Quadratic
* 
*/
const std::unordered_map<int, std::pair<float, float>> PointLight::_attenuationTable = {
    {7, {0.7, 1.8} },
    {13, {0.35, 0.44} },
    {20, {0.22, 0.2} },
    {32, {0.14, 0.07} },
    {50, {0.09, 0.032} },
    {65, {0.07, 0.017} },
    {100, {0.045, 0.075} },
    {160, {0.027, 0.028} }
};
