#include "ResourceManager.hpp"

#include <iostream>
#include <fstream>
#include <unordered_map> 
#include <vector> 

#include "stb_image.h"
#include "Texture.h"


void ResourceManager::DeleteAllResources()
{
	// Delete Textures
	for (auto& texture : _textureCache)
	{
		glDeleteTextures(1, &texture.second);
	}

	// Delete Models
	/*for (auto& models : _modelCache)
	{
		models.second->Delete();
	}*/
}

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

Texture& ResourceManager::LoadTexture(const std::string& path, TextureType type) const
{
	// Check if texture is already loaded
	const auto val = _textureCache.find(path);

	if (val != _textureCache.end())
		return val->second;

	// Otherwise, create and cache a new texture
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// Load image in a local buffer
	int width, height, nrComponents;
	unsigned char* localBuffer = stbi_load(path.c_str, &width, &height, &nrComponents, 0);
	if (!localBuffer) {
		std::cout << "[STBI_IMAGE] Error whe loading image : " << path << std::endl;
		stbi_image_free(localBuffer);
		// [TODO]
		// A remplacer par une execption
		//
		assert("FAILED TO LOAD TEXTURE"); 
	}

	// Fill imageData in order to retrieve pixel color later
	std::vector<unsigned char> imageData = std::vector<unsigned char>(localBuffer, localBuffer + height * height * 4);
	

	GLenum format = 0;
	switch (nrComponents) {
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
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);

	stbi_image_free(localBuffer);

	std::cout << "Resource Manager: loaded texture: " << path << std::endl;

	Texture texture(textureID, type, imageData);

	_textureCache.insert({ path, texture });

	return texture;
}
