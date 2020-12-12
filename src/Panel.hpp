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

	// A appeler � chaque tour de boucle de rendu
	void Panel::Update(FreeflyCamera* camera)
	{
		// GetScreenPostion() : M�thode � coder ! 
		//z = camera->GetScreenPosition();
	}

	//void Panel::Draw() { _mesh.Draw(_shader); }

private:
	void Panel::ComputeModelMatrix(float x, float y, float scale);

	glm::mat4 _modelMatrix;
	std::string _name;

	// Le Mesh poss�de :
	// - La g�ometrie (VAO, VBO, IBO)
	// - Un mat�rial, qui poss�de les textures
	std::shared_ptr<Mesh> _mesh;


	// Je sais pas si t'en auras besoin, mais au cas o�
	bool _visible = true;

};
