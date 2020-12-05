#pragma once

#include <string>
#include <vector>

enum TextureType
{
	DIFFUSE = 0, ROUGHNESS, NORMAL, HEIGHTMAP
};

class Texture
{

public:
	Texture(unsigned int id, TextureType type, const std::vector<unsigned char>& imageData, const std::string& path, int width, int height);
	Texture (const Texture& other);

	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int Width() const { return _width; }
	int Height() const { return _height; }
	unsigned int* IdPtr() { return &_rendererID; }
	unsigned int Id() const { return _rendererID; }
	TextureType Type() const { return _type; }
	std::string Path() const { return _path; }

	const float GetRGB(float x, float y) const;

private:
	Texture();

private:
	unsigned int _rendererID;
	int _width, _height;
	int _BPP = 3;
	TextureType _type;
	std::vector<unsigned char> _imageData;
	std::string _path;
};