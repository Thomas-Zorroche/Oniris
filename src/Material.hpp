#pragma once

#include <string>
#include "glm/glm.hpp"

#include "Texture.h"

/*
* Basic Material and PBR Material Class
* Handle Albedo, Normal and Roughness Texture
*/
class Material
{
public:
	Material();
	//Material(const Material& mat);

	// Create a Basic Material with just a diffuse texture
	void InitBasic(const std::string& name, const std::string& diffusePath);

	// Create PBR Material with textures
	void InitTexturePBR(const std::string& name, const std::string& diffusePath,
		const std::string& normalPath, const std::string& roughnessPath);
	
	// Create PBR Material with colors
	void InitColorPBR(const std::string& name, const glm::vec3& diffuse,
		const glm::vec3& normal, const glm::vec3& roughness);

	unsigned int GetParameterTexture(const TextureType parameter) const;
	unsigned int GetParameterTexture(int index) const;
	glm::vec3 GetParameterColor(const TextureType parameter) const;

	int TextureCount() const { return 1; }

private:
	std::string _name;
	glm::vec3 _materialColor[3];
	std::vector<unsigned int> _materialTexture;
};