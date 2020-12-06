#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"

#include <memory>
#include <string>
#include <iostream>


Scene::Scene(const std::string& pathScene)
	: _terrain(nullptr)
{
	Init(pathScene);
}

Scene::~Scene()
{

}

void Scene::Init(const std::string& pathScene)
{
	std::string sceneFileContent = ResourceManager::Get().LoadTextFile(pathScene);
	std::cout << sceneFileContent << std::endl;

	// Create Terrain
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap16.png");


	// Create Static Meshes
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");
	Model m_portail("res/models/portail/portail.obj");

	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(250, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
}

void Scene::Draw()
{
	// Render the Terrain
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _terrain->GetShader());
	Renderer::Get().SendBlinnPhongUniforms(_terrain->GetShader());
	_terrain->Draw();

	// Render all the static meshes
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		Renderer::Get().SendModelMatrixUniforms(_staticMeshes[i]->GetModelMatrix(), _staticMeshes[i]->GetShader());
		_staticMeshes[i]->Draw();
	}
}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
	_staticMeshesCount++;
}
