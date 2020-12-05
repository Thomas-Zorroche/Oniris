#include "Texture.h"

#include <glad/glad.h>
#include "stb_image.h"
#include <string>

#include <iostream>

Texture::Texture()
	: _rendererID(0), _width(0), _height(0), _type(DIFFUSE)
{
	std::cout << "DEFAULT" << std::endl;
}

Texture& Texture::operator=(const Texture&)
	
{
	std::cout << "= OPERATOR" << std::endl;
}

Texture::Texture(const Texture&)
{
	std::cout << "COPY" << std::endl;
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
	size_t index = _BPP * (y * _height + x);
	
	return _imageData[index + 0]; // Return Red Value
}