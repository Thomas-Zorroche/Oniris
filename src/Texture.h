#pragma once

#include <string>
#include <vector>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	std::string _type;

	std::vector<unsigned char> _image;

	void Texture::ProcessTexture();
public:
	Texture(const std::string& path, std::string type);
	Texture(const Texture& texture);
	
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const { return m_Width; }
	int GetID() const { return m_RendererID; }
	int GetHeight() const { return m_Height; }
	const std::string GetType() const { return _type; }
	const std::string GetPath() const { return m_Filepath; }

	const float GetRGB(float x, float y) const;

};