#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "EntityImporter.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Ocean.hpp"
#include "Skybox.hpp"
#include "ParticuleSystem.hpp"
#include "CollisionManager.hpp"


#include <memory>
#include <string>
#include <vector>
#include <iostream>

void cBoxTestFunction()
{
	std::cout << "Hit Collision LOLILOL" << std::endl;
}


Scene::Scene(const std::string& pathScene)
	: _terrain(nullptr), _ocean(nullptr), _skybox(nullptr)
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



	//Ui shader loading & Hud creation
	ResourceManager::Get().LoadShader("res/shaders/3DTex_ui.vert", "res/shaders/model.frag", "Ui");
	Hud _hud();

	// Load all Shaders
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");
	ResourceManager::Get().LoadShader("res/shaders/Skybox.vert", "res/shaders/Skybox.frag", "Skybox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");


	// Create Terrain
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap16.png");

	// Create Ocean
	//_ocean = std::make_shared<Ocean>();

	// Create Skybox
	std::vector<std::string> facesSkybox
	{
		"night/left.jpg",
		"night/right.jpg",
		"night/top.jpg",
		"night/bottom.jpg",
		"night/front.jpg",
		"night/back.jpg"
	};
	_skybox = std::make_shared<Skybox>(facesSkybox);
	
	// Particule Systems
	auto _particuleSystem = EntityImporter::Get().ParticuleSystems("res/scene/particule_systems.txt", _terrain);
	for (size_t i = 0; i < _particuleSystem.size(); i++)
	{
		//AddParticuleSystem(_particuleSystem[i]);
	}


	Model m_portail("res/models/portail/portail.obj");
	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(450, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
	_staticMeshes[0]->Scale(5.0);

	OnBeginOverlapFunction f = cBoxTestFunction;
	Model m_house("res/models/houses/houses.obj");

	AddStaticMesh(std::make_shared<StaticMesh>(m_house, glm::vec3(550, _terrain->GetHeightOfTerrain(250, 250), 400), "Portail", f, true));
	_staticMeshes[1]->Scale(5.0);
	_staticMeshes[1]->Rotate(90, glm::vec3(0, 1, 0));

	AddStaticMesh(std::make_shared<StaticMesh>(m_house, glm::vec3(550, _terrain->GetHeightOfTerrain(250, 250), 300), "Portail", f, true));
	_staticMeshes[2]->Scale(3.0);
	_staticMeshes[2]->Rotate(270, glm::vec3(0, 1, 0));

	AddStaticMesh(std::make_shared<StaticMesh>(m_house, glm::vec3(750, _terrain->GetHeightOfTerrain(250, 250), 350), "Portail", f, true));
	_staticMeshes[3]->Scale(4.0);
	_staticMeshes[3]->Rotate(180, glm::vec3(0, 1, 0));

}

void Scene::Draw()
{
	// Render the Terrain
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _terrain->GetShader());
	Renderer::Get().SendBlinnPhongUniforms(_terrain->GetShader());
	_terrain->Draw();

	// Render the Ocean
	//_ocean->Draw();

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

	// Render the Skybox
	_skybox->Draw();
	_hud.Draw();
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

