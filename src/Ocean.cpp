#include "Ocean.hpp"
#include "StaticMesh.hpp"
#include "ResourceManager.hpp"

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

Ocean::Ocean()
	: _staticMesh(Model("res/models/ocean/ocean.obj"), glm::vec3(500, 10, 500), "Ocean")
{
	_staticMesh.Scale(1000.0f);
}

void Ocean::Draw() 
{
	auto shader = _staticMesh.GetShader();
	shader->Bind();
	shader->SetUniform1f("u_time", glfwGetTime());
	_staticMesh.Draw();
}