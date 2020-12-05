#pragma once

#include <string>
#include <vector>

enum TextureType
{
	DIFFUSE = 0, HEIGHTMAP, NORMAL, ROUGHNESS
};

class Texture
{

public:
	Texture& operator=(const Texture&);
	Texture (const Texture&);
	
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int Width() const { return _width; }
	int Height() const { return _height; }
	int Id() const { return _rendererID; }
	TextureType Type() const { return _type; }

	const float GetRGB(float x, float y) const;

private:
	Texture();

private:
	unsigned int _rendererID;
	int _width, _height;
	int _BPP;
	TextureType _type;
	std::vector<unsigned char> _imageData;
};