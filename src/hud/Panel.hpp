#pragma once

#include <memory>

#include "opengl/Shader.h"
#include "engine/Camera.hpp"
#include "engine/ResourceManager.hpp"


class Panel
{
public:
	// Constructeur
	Panel(const std::string& texture,  
		const std::string& name,
		float x, 
		float y, 
		float scale,
		int spriteSize,
		int nbSprite,
		bool visibity);
	
	//Draw
	void Draw() const;

	inline bool IsVisible() const { return _visibility; };
	void setVisibility(bool visbility) { _visibility = visbility ; };
	virtual void TranslateTexture(int dir);

private:
	void ComputeModelMatrix(float x, float y, float scale);
	void Scale(float x, float y);
	void Translate(float x, float y);

	glm::mat4 _modelMatrix;

	std::shared_ptr<Mesh> _mesh;

	//sprite parameters
	glm::vec2 _texTranslation;
	float _spriteSize; //in OpenGL context
	int _nbSprite;
	std::string _name;

	bool _visibility = true;

};
