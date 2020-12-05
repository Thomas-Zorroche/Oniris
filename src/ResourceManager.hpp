#pragma once

#include <unordered_map> 
#include "Texture.h"
#include "Shader.h"
#include "Model.hpp"

class ResourceManager
{
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	void DeleteAllResources();

	// Load a text file and return as a string.
	std::string LoadTextFile(const std::string& path) const;

	// Loads an image (if not cached) and generates an OpenGL texture.
	Texture& LoadTexture(const std::string& path, TextureType type) const;
	Texture GetTexture(const std::string& name) const;

	unsigned int LoadShader(const std::string& path, const std::string& name) const;
	Shader GetShader(const std::string& name) const;

	Model LoadObj(const std::string& path, const std::string& name);
	//Model LoadObj(const std::string& path, const std::string& name);

	
	int GetNumLoadedTextures() const noexcept { return _textureCache.size(); }
	int GetNumLoadedModels() const noexcept { return _modelCache.size(); }


private:
	ResourceManager() = default;
	~ResourceManager() = default;

	static std::unordered_map<std::string, Texture> _textureCache;
	static std::unordered_map<std::string, Model> _modelCache;
	//
	// [TODO] :: Material
	//
};

