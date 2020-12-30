#pragma once

#include <unordered_map> 
#include <memory> 
#include <vector> 
#include <string> 
#include "Texture.h"
#include "Shader.h"
#include "Model.hpp"
#include "Shader.h"

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
	Texture LoadTexture(const std::string& path, TextureType type);
	std::vector<unsigned short> LoadHeightmap(const std::string& path, TextureType type);
	
	unsigned int LoadCubemap(const std::vector<std::string>& faces) const;

	void LoadShader(const std::string& vertexShaderPath, 
									   const std::string& fragmentShaderPath,
									   const std::string& name);
	std::shared_ptr<Shader> GetShader(const std::string& name) const;


	std::shared_ptr<Material> GetMaterial(const std::string& name) const;
	std::shared_ptr<Material> CachePBRMaterial(const std::string& name, const std::string& diffuse, 
											   const std::string& roughness, const std::string& normal);
	
	std::shared_ptr<Material> CacheBasicMaterial(const std::string& name, const std::string& diffuse);
	std::shared_ptr<Material> CacheMultipleTexMaterial(const std::string& name, const std::vector<std::string>& filespath);
	std::shared_ptr<Material> CachePBRColorMaterial(const std::string& name, const glm::vec3& diffuse);


	
	int SizeLoadedTextures() const { return _textureCache.size(); }
	int SizeLoadedModels() const { return _modelCache.size(); }
	int SizeLoadedMaterials() const { return _materialCache.size(); }

private:
	ResourceManager() = default;
	~ResourceManager() = default;

	std::unordered_map<std::string, Texture> _textureCache;
	std::unordered_map<std::string, std::shared_ptr<Shader>> _shaderCache;
	std::unordered_map<std::string, std::shared_ptr<Model>> _modelCache;
	std::unordered_map<std::string, std::shared_ptr<Material>> _materialCache;

	//
	// [TODO 3] :: Cache Vertex & Cache Fragment
	//
};

