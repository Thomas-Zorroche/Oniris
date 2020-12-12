#pragma once

#include <memory>

#include "Shader.h"
#include "FreeflyCamera.hpp"
#include "ResourceManager.hpp"


class Panel
{
public:
	// Constructeur
	Panel::Panel(const std::string texture, std::string name, float x, float y, float scale);
	
	//Draw
	void Panel::Draw();

	// A appeler à chaque tour de boucle de rendu
	void Panel::Update(FreeflyCamera* camera)
	{
		// GetScreenPostion() : Méthode à coder ! 
		//z = camera->GetScreenPosition();
	}

	//void Panel::Draw() { _mesh.Draw(_shader); }

private:
	void Panel::ComputeModelMatrix(float x, float y, float scale);

	glm::mat4 _modelMatrix;
	std::string _name;

	// Le Mesh possède :
	// - La géometrie (VAO, VBO, IBO)
	// - Un matérial, qui possède les textures
	std::shared_ptr<Mesh> _mesh;


	// Je sais pas si t'en auras besoin, mais au cas où
	bool _visible = true;

};
