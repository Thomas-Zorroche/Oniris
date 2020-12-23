#include "PointLight.hpp"

PointLight::PointLight(float intensity,
                       const glm::vec3& color,
                       const glm::vec3& position,
                       float radiusAttenuation)
    : BaseLight(intensity, color), _position(position), _radiusAttenuation(radiusAttenuation)
{
    auto it = _attenuationTable.find(radiusAttenuation);
    if (it == _attenuationTable.end())
    {
        throw std::string("Wrong radius size, be sure to check the table in PointLight.cpp and choose an available radius.");
        // Default point light attenuation values
        _radiusAttenuation = 20.0;
        _linear = 0.22;
        _quadratic = 0.2;
    }
    else
    {
        _linear = it->second.first;
        _quadratic = it->second.second;
    }
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
    {100, {0.045, 0.075} }
};
