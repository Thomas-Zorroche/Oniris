#include "ResourceManager.hpp"

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