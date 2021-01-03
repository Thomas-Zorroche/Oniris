#include "engine/Scene.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/EntityImporter.hpp"
#include "engine/Terrain.hpp"
#include "engine/Renderer.hpp"
#include "engine/Ocean.hpp"
#include "engine/Skybox.hpp"
#include "engine/ParticuleSystem.hpp"
#include "engine/ShapeCube.hpp"
#include "engine/Fog.hpp"

#include "opengl/Shader.h"

#include "gameplay/Portal.hpp"
#include "gameplay/Object.hpp"
#include "gameplay/UsableObject.hpp"
#include "gameplay/NarrativeObject.hpp"
#include "gameplay/InteractiveObject.hpp"
#include "gameplay/CreateCrystal.hpp"

#include "collision/CollisionManager.hpp"

#include "lighting/LightManager.hpp"
#include "lighting/PointLight.hpp"
#include "lighting/DirectionalLight.hpp"

#include "hud/Hud.hpp"

#include "gameplay/Game.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>


Scene::Scene(const std::shared_ptr<Game>& game)
	: _terrain(nullptr), _ocean(nullptr), _skybox(nullptr), _fog(std::make_shared<Fog>()),
		_portal(game->PortalPtr())
{
	Init(game);
}

Scene::~Scene() {}

void Scene::Init(const std::shared_ptr<Game>& game)
{
	// Init fog into game
	// ==================
	game->SetFog(_fog);

	// Create Terrain
	// ==============
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/Terrain/heightmap.png");

	// Create Ocean
	// ============
	_ocean = std::make_shared<Ocean>(_fog);

	// Create Skybox
	// =============
	std::vector<std::string> facesSkybox
	{
		"night2/left.png",
		"night2/right.png",
		"night2/up.png",
		"night2/down.png",
		"night2/front.png",
		"night2/back.png"
	};
	_skybox = std::make_shared<Skybox>(facesSkybox);

	// Create an Entity Importer
	// =========================
	EntityImporter entityImporter;

	// Particule Systems
	// =================
	auto particuleSystem = entityImporter.ParticuleSystems("res/scene/particule_systems.txt", _terrain, _fog);
	for (size_t i = 0; i < particuleSystem.size(); i++)
	{
		AddParticuleSystem(particuleSystem[i]);
	}

	// Import Static Meshes
	// ====================
	auto staticMeshes = entityImporter.StaticMeshes("res/scene/static_meshes.txt", _terrain, _fog);
	for (size_t i = 0; i < staticMeshes.size(); i++)
	{
		AddStaticMesh(staticMeshes[i]);
	}

	// Hud creation
	// ============
	Hud::Get().Init();

	// Create Objects
	// ==============
	auto objectsEntities = entityImporter.Objects("res/scene/objects.txt", _terrain, _fog, game);
	_objects = objectsEntities.objects;
	for (const auto& obj : objectsEntities.ioObjects)
	{
		AddStaticMesh(obj);
	}

	//create crystal
	CreateCrystal crystal = CreateCrystal(_objects, _terrain, game);

	// Load All Lights
	// =================
	LightManager::Get().LoadAllLights(_terrain, _portal, crystal);
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

	// Draw Hud
	// ===========
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

void Scene::Free()
{
	// Free all static meshes
	// ==========================
	for (size_t i = 0; i < _staticMeshesCount; i++)
		_staticMeshes[i]->Free();

	// Free all objects
	// ==========================
	for (auto pair : _objects)
	{
		auto obj = pair.second;
		obj->Free();
	}

	// Free all panels (hud)
	// ==========================
	Hud::Get().Free();

	// Free all textures 
	// ==========================
	ResourceManager::Get().DeleteAllResources();
}

