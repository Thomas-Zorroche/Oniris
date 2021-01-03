#include "engine/Ocean.hpp"
#include "engine/StaticMesh.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Fog.hpp"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

Ocean::Ocean(const std::shared_ptr<Fog>& fog)
	: _staticMesh(Model("res/models/ocean/ocean.obj"), TransformLayout(glm::vec3(500, 11, 500)), "Ocean", fog)
{
	_staticMesh.Scale(1000.0f);
}

void Ocean::Draw(const std::shared_ptr<Fog>& fog)
{
	auto shader = _staticMesh.GetShader();
	shader->Bind();

	shader->SetUniform1f("u_fogDensity", fog->Density());
	shader->SetUniform1f("u_fogGradient", fog->Gradient());
	shader->SetUniform1f("u_time", glfwGetTime());
	shader->SetUniform3f("u_skyColor", fog->ColorSky());
	_staticMesh.Draw();
}