#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "EntityImporter.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Ocean.hpp"
#include "Skybox.hpp"
#include "ParticuleSystem.hpp"

#include "Portal.hpp"
#include "Object.hpp"
#include "UsableObject.hpp"
#include "NarrativeObject.hpp"
#include "InteractiveObject.hpp"

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
#include <unordered_map>


Scene::Scene(const std::string& pathScene, const std::shared_ptr<Game>& game)
	: _terrain(nullptr), _ocean(nullptr), _skybox(nullptr), _fog(std::make_shared<Fog>()),
		_portal(game->PortalPtr())
{
	Init(pathScene, game);
}

Scene::~Scene()
{

}

void Scene::Init(const std::string& pathScene, const std::shared_ptr<Game>& game)
{
	// Init fog into game
	// ==================
	game->SetFog(_fog);

	// Create Terrain
	// ==============
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/heightmap_rotate.png");

	// Load All Lights
	// =================
	LightManager::Get().LoadAllLights(_terrain, _portal);

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
	for (size_t i = 0; i < particuleSystem.size(); i++)
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

	// Ui shader loading & Hud creation
	// ================================
	ResourceManager::Get().LoadShader("res/shaders/3DTex_ui.vert", "res/shaders/ui.frag", "Ui");
	Hud::Get().Init();

	// Create Objects
	// ==============
	auto objectsEntities = EntityImporter::Get().Objects("res/scene/objects.txt", _terrain, _fog, game);
	_objects = objectsEntities.objects;
	for (const auto& obj : objectsEntities.ioObjects)
	{
		AddStaticMesh(obj);
	}
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
	_ocean->Draw(_fog);

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
			glDepthMask(GL_FALSE);
		
		_particuleSystem[i]->Draw();
		
		if (_particuleSystem[i]->Name() == "Grass")
			glDepthMask(GL_TRUE);
	}

	//Render all Objects (Narratives & Usable)
	//========================================
	for (auto pair : _objects)
	{
		auto obj = pair.second;

		if (obj->IsInWorld())
			obj->Draw();
	}

	// Draw portal
	// ===========
	_portal->Draw();

	Hud::Get().Draw();
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

