#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "EntityImporter.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Ocean.hpp"
#include "ParticuleSystem.hpp"

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

	// Load all Shaders
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");

	// Create Terrain
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap16.png");

	// Create Ocean
	_ocean = std::make_shared<Ocean>();
	
	// Particule Systems
	auto _particuleSystem = EntityImporter::Get().ParticuleSystems("res/scene/particule_systems.txt", _terrain);
	for (size_t i = 0; i < _particuleSystem.size(); i++)
	{
		AddParticuleSystem(_particuleSystem[i]);
	}
	

	//ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Trees.frag", "Trees");
	//Model m_tree("res/models/trees/Sapin_01.obj");
	//AddStaticMesh(std::make_shared<StaticMesh>(m_tree, glm::vec3(250, _terrain->GetHeightOfTerrain(250, 250), 250), "Trees"));

	//ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");
	//Model m_portail("res/models/portail/portail.obj");
	//AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(350, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
}

void Scene::Draw()
{
	// Render the Terrain
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _terrain->GetShader());
	Renderer::Get().SendBlinnPhongUniforms(_terrain->GetShader());
	_terrain->Draw();

	// Render the Ocean
	//Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _terrain->GetShader());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_ocean->Draw();
	glDisable(GL_BLEND);


	// Render all the static meshes
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		//Renderer::Get().SendModelMatrixUniforms(_staticMeshes[i]->GetModelMatrix(), _staticMeshes[i]->GetShader());
		_staticMeshes[i]->Draw();
	}

	// Render all the particule systems
	
	for (size_t i = 0; i < _particuleSystemCount; i++)
	{
		_particuleSystem[i]->Draw();
	}
}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
	_staticMeshesCount++;
}

void Scene::AddParticuleSystem(const std::shared_ptr<ParticuleSystem>& particuleSystem)
{
	_particuleSystem.push_back(particuleSystem);
	_particuleSystemCount++;
}

