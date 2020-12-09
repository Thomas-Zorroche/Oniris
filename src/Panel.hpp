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

	// A appeler � chaque tour de boucle de rendu
	void Panel::Update(FreeflyCamera* camera)
	{
		// GetScreenPostion() : M�thode � coder ! 
		//z = camera->GetScreenPosition();
	}

	//void Panel::Draw() { _mesh.Draw(_shader); }

private:
	// Coordinates :
	// Par convention, on va dire que la pannel apparait de base en haut
	// � gauche, donc au point x = 0 et y = 0
	// Les coordonn�es x et y sont donc dans le rep�re relatif de l'�cran
	// La coordonn�e suivant z est celle de la camera, elle est chang�e � 
	// chaque appel de Update()
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	// Le Mesh poss�de :
	// - La g�ometrie (VAO, VBO, IBO)
	// - Un mat�rial, qui poss�de les textures
	// (Un BasicInit devrait suffire, tu as besoin que d'une diffuse texture)
	Mesh _mesh;

	// Cr�er un shader avec deux fichiers source : Pannel.vert, Pannel.frag
	// C'est le m�me dans tous les shaders
	// Utiliser le shader dans le draw
	Shader _shader;

	// Je sais pas si t'en auras besoin, mais au cas o�
	bool _visible = true;

};
