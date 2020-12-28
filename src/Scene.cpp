#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "EntityImporter.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Ocean.hpp"
#include "Skybox.hpp"
#include "ParticuleSystem.hpp"
#include "UsableObject.hpp"
#include "NarrativeObject.hpp"
#include "CollisionManager.hpp"

#include "LightManager.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

#include "ShapeCube.hpp"
#include "Object.hpp"
#include "Fog.hpp"
#include "Hud.hpp"
#include "Game.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iostream>


Scene::Scene(const std::string& pathScene)
	: _terrain(nullptr), _ocean(nullptr), _skybox(nullptr), _fog(std::make_shared<Fog>())
{
	Init(pathScene);
}

Scene::~Scene()
{

}

void Scene::Init(const std::string& pathScene)
{
	// Read scene file : load all resources needed to the scene [TODO]
	// ========================================================
	std::string sceneFileContent = ResourceManager::Get().LoadTextFile(pathScene);

	// Ui shader loading & Hud creation
	// ================================
	ResourceManager::Get().LoadShader("res/shaders/3DTex_ui.vert", "res/shaders/model.frag", "Ui");
	Hud::Get().Init();

	// Load all Shaders
	// ================
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");
	ResourceManager::Get().LoadShader("res/shaders/Skybox.vert", "res/shaders/Skybox.frag", "Skybox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Model3D_Tex");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/cbox.frag", "CBox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Key");

	// Create Terrain
	// ==============
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse_blue.jpg", "res/img/heightmap_rotate.png");

	// Create All Lights
	// =================
	std::shared_ptr<BaseLight> dirLight = std::make_shared<DirectionalLight>(
		1.0f,
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(1, 1, 1)
		);
	std::shared_ptr<BaseLight> pointLight = std::make_shared<PointLight>(
		1.0f,
		glm::vec3(1, 0.6, 0),
		glm::vec3(604, _terrain->GetHeightOfTerrain(604, 204), 204),
		160.0f);
	LightManager::Get().AddLight(dirLight, LightType::DIR);
	LightManager::Get().AddLight(pointLight, LightType::POINT);

	// Create Ocean
	// ============
	_ocean = std::make_shared<Ocean>(_fog);

	// Create Skybox
	// =============
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
	// =================
	auto particuleSystem = EntityImporter::Get().ParticuleSystems("res/scene/particule_systems.txt", _terrain, _fog);
	for (size_t i = 0; i < _particuleSystem.size(); i++)
	{
		AddParticuleSystem(particuleSystem[i]);
	}

	// Import Static Meshes
	// ====================
	auto staticMeshes = EntityImporter::Get().StaticMeshes("res/scene/static_meshes.txt", _terrain, _fog);
	for (size_t i = 0; i < staticMeshes.size(); i++)
	{
		AddStaticMesh(staticMeshes[i]);
	}


	// Create Objects
	// ==============
	//_objects = EntityImporter::Get().Objects("res/scene/objects.txt", _terrain);

	// Init Game
	// =========
	Game::Get().SetRefObjects(&_objects);
}

void Scene::Draw()
{
	// Render the Skybox
	// =================
	_skybox->Draw(_fog);
	
	// Render the Terrain
	// ==================
	_terrain->Draw(_fog);

	// Render the Ocean
	// ================
	//_ocean->Draw(_fog);

	// Render all the static meshes
	// ============================
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		_staticMeshes[i]->Draw();
	}

	// Render all the particule systems
	// ================================
	for (size_t i = 0; i < _particuleSystemCount; i++)
	{
		if (_particuleSystem[i]->Name() == "Grass")
		{
			glDepthMask(GL_FALSE);
		}
		_particuleSystem[i]->Draw();
	}
	glDepthMask(GL_TRUE);

	//Render all Objects (Narratives & Usable)
	//========================================
	//for (auto pair : _objects)
	//{
	//	auto obj = pair.second;
	//	//std::cout << pair.first << "-" << obj->IsInWorld() << std::endl;
	//	if (obj->IsInWorld())
	//		obj->Draw();
	//}


	
	
	//Hud::Get().Draw();
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

//void Scene::AddObject(const std::string& name, const std::shared_ptr<Object>& object) {
//	_objects.insert({name, object});
//}
