#include "engine/Fog.hpp"


// Getters
std::pair<glm::vec3, glm::vec3> Fog::Color() const 
{ 
	return { _colorShadow, _colorSun }; 
}
glm::vec3 Fog::ColorSky() const 
{ 
	if (!_darkWorld)
		return _colorSky; 
	else
		return _colorSkyDW;
}
const float Fog::Density() const
{ 
	return _density; 
}
const float Fog::Gradient() const
{ 
	return _gradient; 
}
const float Fog::Height() const
{ 
	return _height; 
}
const float Fog::LowerLimit() const
{ 
	return _lowerLimit; 
}
const float Fog::UpperLimit() const
{ 
	return _upperLimit; 
}






// Setters
void Fog::InsideDarkWorld(bool darkWorld)
{
	_darkWorld = darkWorld;
}