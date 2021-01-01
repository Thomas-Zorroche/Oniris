#pragma once

#include "Object.hpp"
#include "StaticMesh.hpp"
#include "Game.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

class Model;
class TransformLayout;

class Portal : public Object
{
public:
	Portal(const Model& model, const TransformLayout& transLayout)
		: Object(model, transLayout, "Portal") {}
	
	void OnOverlap() override
	{
		Game::Get().
	}

	void Open()
	{
		_open = true;
	}

	void Draw()
	{
		if (_open)
		{
			auto shader = _staticMesh->GetShader();
			shader->Bind();
			shader->SetUniform1f("u_time", glfwGetTime());
			_staticMesh->Draw();
		}
			
	}

private:
	bool _open = false;
};