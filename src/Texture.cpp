#include "Texture.h"

#include <glad/glad.h>
#include "stb_image.h"
#include <string>

#include <iostream>


Texture::Texture(const std::string& path, std::string type)
	: m_RendererID(0), m_Filepath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), _type(type)
{
	std::cout << "Default Constructor" << std::endl;
	ProcessTexture();
}

Texture::Texture(const Texture& texture)
	: m_RendererID(0), m_Filepath(texture.m_Filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), _type(texture._type)
{
	std::cout << "Copy Constructor" << std::endl;
	ProcessTexture();
}

void Texture::ProcessTexture()
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const 
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}