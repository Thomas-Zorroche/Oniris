#include "ResourceManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map> 
#include <vector> 

#include "stb_image.h"
#include "Texture.h"
#include "Material.hpp"
#include "Shader.h"


void ResourceManager::DeleteAllResources()
{
	// Delete Textures
	for (auto& texture : _textureCache)
	{
		glDeleteTextures(1, texture.second.IdPtr());
	}

	// Delete Models
	/*for (auto& models : _modelCache)
	{
		models.second->Delete();
	}*/
}

//
// ------------------------------ Textures ------------------------------ 
//

std::string ResourceManager::LoadTextFile(const std::string& path) const {
	std::ifstream ifs(path);

	if (!ifs) {
		std::cerr << "Resource Manager: File loading error: " + path << std::endl;
		return "";
	}
	
	std::string content ((std::istreambuf_iterator<char>(ifs)),
						 (std::istreambuf_iterator<char>()));

	return content;
}

Texture ResourceManager::LoadTexture(const std::string& path, TextureType type)
{
	// Check if texture is already loaded in the cache
	const auto val = _textureCache.find(path);
	if (val != _textureCache.end())
		return val->second;

	// Otherwise, create and cache a new texture
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Load image in a local buffer
	int width, height, BPP;
	unsigned char* localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);
	if (!localBuffer) {
		std::cout << "[STBI_IMAGE] Error whe loading image : " << path << std::endl;
		stbi_image_free(localBuffer);
		// 
		// [TODO 2] :: A remplacer par une execption
		//
		assert("FAILED TO LOAD TEXTURE"); 
	}

	// Fill imageData in order to retrieve pixel color later
	// 
	// [TODO 1] :: Just do this for heightmaps
	//
	std::vector<unsigned char> imageData(localBuffer, localBuffer + height * height * 4);
	
	GLenum format = 0;
	switch (BPP) {
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	glBindTexture(GL_TEXTURE_2D, 0);


	stbi_image_free(localBuffer);

	std::cout << "Resource Manager: loaded texture: " << path << std::endl;

	Texture texture(textureID, type, imageData, path, width, height);

	_textureCache.insert({ path, texture });

	return texture;
}

//
// ------------------------------ Materials ------------------------------ 
//

std::shared_ptr<Material> ResourceManager::GetMaterial(const std::string& name) const
{
	// Check if material exists
	const auto mat = _materialCache.find(name);
	
	if (mat == _materialCache.end())
		return nullptr;

	return mat->second;
}

std::shared_ptr<Material> ResourceManager::CachePBRMaterial(const std::string& name, const std::string& diffuse,
	const std::string& roughness, const std::string& normal)
{
	Material mat = Material();
	mat.InitTexturePBR(name, diffuse, roughness, normal);

	return _materialCache.insert({ name, std::make_shared<Material>(mat) }).first->second;

}

std::shared_ptr<Material> ResourceManager::CacheBasicMaterial(const std::string& name, const std::string& diffuse)
{
	Material mat = Material();
	mat.InitBasic(name, diffuse);

	return _materialCache.insert({ name, std::make_shared<Material>(mat) }).first->second;
}

std::shared_ptr<Material> ResourceManager::CachePBRColorMaterial(const std::string& name, const glm::vec3& diffuse)
{
	Material mat = Material();
	mat.InitColorPBR(name, diffuse, glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));

	return _materialCache.insert({ name, std::make_shared<Material>(mat) }).first->second;
}

//
// ------------------------------ Shaders ------------------------------ 
//
void ResourceManager::LoadShader(const std::string& vertexShaderPath, 
													const std::string& fragmentShaderPath, 
													const std::string& name)
{
	// If shader already exists, do not load it again
	const auto shader = GetShader(name);
	if (!shader)
	{
		std::string vertexCode;
		std::string fragmentCode;
		try
		{
			// open file
			std::ifstream vertexShaderFile(vertexShaderPath);
			std::ifstream fragmentShaderFile(fragmentShaderPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}
		//
		// [TODO 2] :: Vérifier cette execption
		// 

		std::shared_ptr<Shader> newShader = std::make_shared<Shader>(vertexCode, fragmentCode);
	
		_shaderCache.insert({ name, newShader}).first->second;
	}
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name) const
{
	// Check if shader exists
	const auto shader = _shaderCache.find(name);

	if (shader == _shaderCache.end())
		return nullptr;

	return shader->second;
}

