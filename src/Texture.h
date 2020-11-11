#pragma once

#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	std::string _type;
public:
	Texture(const std::string& path, std::string type);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetID() const { return m_RendererID; }
	inline int GetHeight() const { return m_Height; }
	inline const std::string GetType() const { return _type; }
};