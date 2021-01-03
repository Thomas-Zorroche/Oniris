#pragma once

#include <string>
#include <memory>
#include "glm/glm.hpp"

#include "opengl/Texture.h"

class Shader;

/*
* Basic Material and PBR Material Class
* Handle Albedo, Normal and Roughness Texture
*/
class Material
{
public:
	Material();

	// Create a Basic Material with just a diffuse texture
	void InitBasic(const std::string& name, const std::string& diffusePath);

	// Create PBR Material with textures
	void InitTexturePBR(const std::string& name, const std::string& diffusePath,
		const std::string& normalPath, const std::string& roughnessPath);
	
	// Create PBR Material with colors
	void InitColorPBR(const std::string& name, const glm::vec3& color, float shininess);
	
	// Create Material with multiples textures
	void InitMulipleTextures(const std::string& name, const std::vector<std::string>& texturesPath);

	unsigned int GetParameterTexture(const TextureType parameter) const;
	unsigned int GetParameterTexture(int index) const;
	glm::vec3 GetParameterColor(const TextureType parameter) const;

	int TextureCount() const { return _materialTextures.size(); }

	void SendMaterialUniform(std::shared_ptr<Shader>& shader);

	// Getters Parameters
	const glm::vec3& Ambient() const { return _ambient; }
	const glm::vec3& Diffuse() const { return _diffuse; }
	const glm::vec3& Specular() const { return _specular; }
	float Shininess() const { return _shininess; }


private:

	float _shininess;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;

	std::vector<unsigned int> _materialTextures;
	std::string _name;

	const static int NumberTexturesMax;
};

