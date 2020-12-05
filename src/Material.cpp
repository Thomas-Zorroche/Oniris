#include "Material.hpp"

#include "ResourceManager.hpp"
#include "Texture.h"

#include "glm/glm.hpp"

#include <iostream>


Material::Material()
	: _materialColor { glm::vec3(0.0f), glm::vec3(0.0f) , glm::vec3(0.0f) },
	  _materialTexture { 0, 0, 0 } {}

//Material::Material(const Material& m)
//	: _name(m._name),
//	  _materialColor{ m._materialColor[0], m._materialColor[1] , m._materialColor[2] },
//	  _materialTexture{ m._materialTexture[0], m._materialTexture[1], m._materialTexture[2] } 
//{
//	std::cout << "[MATERIAL] COPY CONSTRUCTOR" << std::endl;
//}



void Material::InitBasic(const std::string& name, const std::string& diffusePath)
{
	_name = name;

	_materialTexture[DIFFUSE] = ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE).Id();
}

void Material::InitTexturePBR(const std::string& name, const std::string& diffusePath,
	const std::string& normalPath, const std::string& roughnessPath)
{
	_name = name;

	_materialTexture[DIFFUSE] = ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE).Id();
	_materialTexture[ROUGHNESS] = ResourceManager::Get().LoadTexture(roughnessPath, ROUGHNESS).Id();
	_materialTexture[NORMAL] = ResourceManager::Get().LoadTexture(normalPath, NORMAL).Id();
}

void Material::InitColorPBR(const std::string& name, const glm::vec3& diffuse,
	const glm::vec3& normal, const glm::vec3& roughness)
{
	_name = name;

	_materialColor[DIFFUSE] = diffuse;
	_materialColor[ROUGHNESS] = roughness;
	_materialColor[NORMAL] = normal;
}

unsigned int Material::GetParameterTexture(const TextureType parameter) const
{
	return _materialTexture[parameter];
}

unsigned int Material::GetParameterTexture(int index) const
{
	return _materialTexture[index];
}

glm::vec3 Material::GetParameterColor(const TextureType parameter) const
{
	return _materialColor[parameter];
}