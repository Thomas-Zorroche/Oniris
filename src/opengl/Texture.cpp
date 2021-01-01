#include "opengl/Texture.h"

#include <glad/glad.h>
#include "stb_image.h"
#include <string>

#include <iostream>

Texture::Texture()
	: _rendererID(0), _width(0), _height(0), _type(DIFFUSE)
{
}

Texture::Texture(const Texture& other)
{
	if (this != &other)
	{
		_rendererID = other._rendererID;
		_type = other._type;
		_imageData = other._imageData;
		_path = other._path;
		_width = other._width;
		_height = other._height;
	}
}

Texture::Texture(unsigned int id, TextureType type, const std::vector<unsigned char>& imageData, const std::string& path, int width, int height)
	: _rendererID(id), _type(type), _imageData(imageData), _path(path), _width(width), _height(height)
{
}


Texture::~Texture()
{
}

void Texture::Bind(unsigned int slot) const 
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _rendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

const float Texture::GetRGB(float x, float y) const
{
	size_t index = y * _height + x;
	
	return _imageData[index]; // Return Red Value
}