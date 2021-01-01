#include "gameplay/Portal.hpp"
#include "engine/Fog.hpp"
#include "lighting/BaseLight.hpp"


Portal::Portal()
	: _staticMesh(Model("res/models/PortalPlan.obj"), TransformLayout(glm::vec3(499, 75, 578), glm::vec3(0, 0, 0), 2.2f), "Portal", nullptr)
{}

void Portal::Open()
{
	_open = true;
}

void Portal::Draw()
{
	if (_hitsCountCBox == 1)
		_canEnter = true;
	
	_hitsCountCBox = 0;

	if (_open)
	{
		_light->SetIntensity(6.0f);

		auto shader = _staticMesh.GetShader();
		shader->Bind();
		shader->SetUniform1f("u_time", glfwGetTime());
		_staticMesh.Draw();
	}
}

void Portal::HitCBox()
{
	_hitsCountCBox++;

	if (_hitsCountCBox == 2 && _canEnter && _open)
	{
		_canEnter = false;
		if (_darkWorld)
		{
			_darkWorld = false;
			_fog->InsideDarkWorld(false);
		}
		else
		{
			_darkWorld = true;
			_fog->InsideDarkWorld(true);
		}


	}
}

void Portal::SetFog(const std::shared_ptr<Fog>& fog)
{
	_fog = fog;
}

void Portal::SetLight(const std::shared_ptr<BaseLight>& light)
{
	_light = light;
}