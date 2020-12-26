#include "Material.hpp"

#include "ResourceManager.hpp"
#include "Texture.h"

#include "glm/glm.hpp"

#include <iostream>


Material::Material()
	: _shininess(1.0f), _ambient(glm::vec3(0.8, 0.8, 0.8)), _diffuse(glm::vec3(0.8, 0.8, 0.8)), _specular(glm::vec3(0.5, 0.5, 0.5)),
	  _materialTextures { 0, 0, 0 } {}

/*
* InitBasic		 : Basic material with just a diffuse texutre
* InitTexturePBR : PBR material wiht diffuse, rougness and normal textures
* InitColorPBR   : PBR material with const vec3 colors as parameters
*/
void Material::InitBasic(const std::string& name, const std::string& diffusePath)
{
	_name = name;

	_materialTextures[DIFFUSE] = ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE).Id();
}

void Material::InitTexturePBR(const std::string& name, const std::string& diffusePath,
	const std::string& normalPath, const std::string& roughnessPath)
{
	_name = name;

	_materialTextures[DIFFUSE] = ResourceManager::Get().LoadTexture(diffusePath, DIFFUSE).Id();
	_materialTextures[ROUGHNESS] = ResourceManager::Get().LoadTexture(roughnessPath, ROUGHNESS).Id();
	_materialTextures[NORMAL] = ResourceManager::Get().LoadTexture(normalPath, NORMAL).Id();
}

void Material::InitColorPBR(const std::string& name, const glm::vec3& color, float shininess)
{
	_name = name;

	_diffuse = color;
	_ambient = color;
	_specular = glm::vec3(0.5, 0.5, 0.5);

	_shininess = shininess;
}


/*
* Getter Parameter
*/
unsigned int Material::GetParameterTexture(const TextureType parameter) const
{
	return _materialTextures[parameter];
}
unsigned int Material::GetParameterTexture(int index) const
{
	return _materialTextures[index];
}


/*
* Send Uniforms
*/
void Material::SendMaterialUniform(std::shared_ptr<Shader>& shader)
{
	shader->SetUniform3f("material.ambient", _ambient);
	shader->SetUniform3f("material.diffuse", _diffuse);
	shader->SetUniform3f("material.specular", _specular);
	shader->SetUniform1f("material.shininess", _shininess);
}