#pragma once

#include <memory>

#include "Shader.h"
#include "Camera.hpp"
#include "ResourceManager.hpp"


class Panel
{
public:
	// Constructeur
	Panel::Panel(const std::string& texture,  
		const std::string& name,
		float x, 
		float y, 
		float scale,
		int spriteSize,
		int nbSprite,
		bool visibity);
	
	//Draw
	void Draw() const;

	// A appeler à chaque tour de boucle de rendu
	void Update(Camera* camera);

	inline bool IsVisible() const { return _visibility; };
	void setVisibility(bool visbility) { _visibility = visbility ; };
	virtual void TranslateTexture(int dir);
	const std::string& GetName() const { return _name; }

private:
	void ComputeModelMatrix(float x, float y, float scale);
	void Scale(float x, float y);
	void Translate(float x, float y);


	glm::mat4 _modelMatrix;

	// Le Mesh possède :
	// - La géometrie (VAO, VBO, IBO)
	// - Un matérial, qui possède les textures
	std::shared_ptr<Mesh> _mesh;

	//sprite parameters
	glm::vec2 _texTranslation;
	float _spriteSize; //in OpenGL context
	int _nbSprite;
	std::string _name;

	// Je sais pas si t'en auras besoin, mais au cas où
	bool _visibility = true;

};
