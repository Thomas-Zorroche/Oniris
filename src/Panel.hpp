#pragma once

#include <memory>

#include "Shader.h"
#include "FreeflyCamera.hpp"
#include "ResourceManager.hpp"


class Panel
{
public:
	// Constructeur
	Panel::Panel(const std::string texture, 
		std::string name, 
		float x, 
		float y, 
		float scale,
		int spriteSize,
		int nbSprite,
		bool visibity);
	
	//Draw
	void Panel::Draw();

	// A appeler à chaque tour de boucle de rendu
	void Panel::Update(FreeflyCamera* camera);

	inline bool Panel::IsVisible(){ return _visibility; };

private:
	void Panel::ComputeModelMatrix(float x, float y, float scale);
	void Panel::Scale(float x, float y);
	void Panel::Translate(float x, float y);
	void Panel::TranslateTexture();


	glm::mat4 _modelMatrix;
	std::string _name;

	// Le Mesh possède :
	// - La géometrie (VAO, VBO, IBO)
	// - Un matérial, qui possède les textures
	std::shared_ptr<Mesh> _mesh;

	//sprite parameters
	glm::vec2 _texTranslation;
	float _spriteSize; //in OpenGL context
	int _nbSprite;


	// Je sais pas si t'en auras besoin, mais au cas où
	bool _visibility = true;

};
