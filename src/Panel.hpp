#pragma once

#include <memory>

#include "Texture.h"
#include "FreeflyCamera.hpp"
#include "ResourceManager.hpp"



class Panel
{
public:
	// Constructeur
	//Panel::Panel(const Texture& texture);

	// A appeler à chaque tour de boucle de rendu
	void Panel::Update(FreeflyCamera* camera)
	{
		// GetScreenPostion() : Méthode à coder ! 
		//z = camera->GetScreenPosition();
	}

	//void Panel::Draw() { _mesh.Draw(_shader); }

private:
	// Coordinates :
	// Par convention, on va dire que la pannel apparait de base en haut
	// à gauche, donc au point x = 0 et y = 0
	// Les coordonnées x et y sont donc dans le repère relatif de l'écran
	// La coordonnée suivant z est celle de la camera, elle est changée à 
	// chaque appel de Update()
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	// Le Mesh possède :
	// - La géometrie (VAO, VBO, IBO)
	// - Un matérial, qui possède les textures
	// (Un BasicInit devrait suffire, tu as besoin que d'une diffuse texture)
	Mesh _mesh;

	// Créer un shader avec deux fichiers source : Pannel.vert, Pannel.frag
	// C'est le même dans tous les shaders
	// Utiliser le shader dans le draw
	Shader _shader;

	// Je sais pas si t'en auras besoin, mais au cas où
	bool _visible = true;

};
