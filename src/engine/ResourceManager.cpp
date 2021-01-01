#include "engine/ResourceManager.hpp"
#include "engine/Log.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map> 
#include <vector> 
#include <string> 

#include "stb_image.h"
#include "opengl/Texture.h"
#include "engine/Material.hpp"
#include "opengl/Shader.h"


void ResourceManager::DeleteAllResources()
{
	// Delete Textures
	for (auto& texture : _textureCache)
	{
		glDeleteTextures(1, texture.second.IdPtr());
	}


}

//
// ------------------------------ Textures ------------------------------ 
//
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

	if (!localBuffer)
	{
		throw std::string("[STBI_IMAGE] Error whe loading image : " + path);
		stbi_image_free(localBuffer);
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (Log::Get().Level() >= LogLevel::INFO)
		std::cout << "[Resource Manager] : loaded texture: " << path << std::endl;
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	Texture texture(textureID, type, std::vector<unsigned char>(), path, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(localBuffer);
	_textureCache.insert({ path, texture });
	return texture;
}

std::vector<unsigned short> ResourceManager::LoadHeightmap(const std::string& path, TextureType type)
{
	// Load image in a local buffer
	int width, height, BPP;
	unsigned short* localBuffer = stbi_load_16(path.c_str(), &width, &height, &BPP, 1);

	if (!localBuffer) {
		std::cout << "[STBI_IMAGE] Error whe loading image : " << path << std::endl;
		stbi_image_free(localBuffer);
		// 
		// [TODO 2] :: A remplacer par une execption
		//
		assert("FAILED TO LOAD TEXTURE");
	}
	// Fill imageData in order to retrieve pixel color later
	std::vector<unsigned short> imageData(localBuffer, localBuffer + height * height);
	
	if (Log::Get().Level() >= LogLevel::INFO)
		std::cout << "[Resource Manager] : loaded texture: " << path << std::endl;

	stbi_image_free(localBuffer);

	return imageData;
}

unsigned int ResourceManager::LoadCubemap(const std::vector<std::string>& faces) const
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, BPP;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::string path = "res/img/skybox/" + faces[i];
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &BPP, 4);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "[STBI_IMAGE] Error when loading cubemap: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	if (Log::Get().Level() >= LogLevel::INFO)
		std::cout << "[Resource Manager] : loaded skybox" << std::endl;

	return textureID;
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

std::shared_ptr<Material> ResourceManager::CacheMultipleTexMaterial(const std::string& name, const std::vector<std::string>& filespath)
{
	Material mat = Material();
	try
	{
		mat.InitMulipleTextures(name, filespath);
	}
	catch (const std::string& e)
	{
		std::cerr << "[Resource Manager] :: " << e << std::endl;
	}

	return _materialCache.insert({ name, std::make_shared<Material>(mat) }).first->second;
}


std::shared_ptr<Material> ResourceManager::CachePBRColorMaterial(const std::string& name, const glm::vec3& diffuse)
{
	Material mat = Material();
	mat.InitColorPBR(name, diffuse, 32.0f);

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

void ResourceManager::LoadAllShaders()
{
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/portal.frag", "Portal");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");
	ResourceManager::Get().LoadShader("res/shaders/Skybox.vert", "res/shaders/Skybox.frag", "Skybox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Model3D_Tex");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/cbox.frag", "CBox");

	ResourceManager::Get().LoadShader("res/shaders/3DTex_ui.vert", "res/shaders/ui.frag", "Ui");

	ResourceManager::Get().LoadShader("res/shaders/Particule.vert", "res/shaders/modelAlpha.frag", "ParticuleAlpha");
	ResourceManager::Get().LoadShader("res/shaders/Particule.vert", "res/shaders/model.frag", "Particule");


}

