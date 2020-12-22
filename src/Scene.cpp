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
#include "ShapeCube.hpp"
#include "Object.hpp"
#include "Fog.hpp"

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
	Hud _hud();

	// Load all Shaders
	// ================
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");
	ResourceManager::Get().LoadShader("res/shaders/Skybox.vert", "res/shaders/Skybox.frag", "Skybox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/cbox.frag", "CBox");
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Key");


	// Create Terrain
	// ==============
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap.png");

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
	auto _particuleSystem = EntityImporter::Get().ParticuleSystems("res/scene/particule_systems.txt", _terrain, _fog);
	for (size_t i = 0; i < _particuleSystem.size(); i++)
	{
		AddParticuleSystem(_particuleSystem[i]);
	}

	// Import Models
	// =============
	Model m_portail("res/models/portail/portail.obj");
	Model m_house("res/models/houses/houses.obj");
	//Model m_key("res/models/key/key.obj");
	//Model m_map("res/models/map/map.obj");


	// Define Collisions Layout for Static Mesh's cBox
	// ===============================================
	CollisionLayout cLayout_House(true, true, false);

	//_objects = EntityImporter::Get().Objects("res/scene/objects.txt", _terrain);

	// Create Static Meshes
	// ====================
	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(300, _terrain->GetHeightOfTerrain(300, 550), 550), "Portail", nullptr));
	AddStaticMesh(std::make_shared<StaticMesh>(m_house, glm::vec3(200, _terrain->GetHeightOfTerrain(200, 400), 400), "Portail", nullptr, cLayout_House));

	
	// Do all the Transformations on Static Meshes
	// ===========================================
	try
	{
		_staticMeshes[0]->Scale(1.0);
		_staticMeshes[1]->Scale(2.0);
		_staticMeshes[1]->Rotate(90, glm::vec3(0, 1, 0));
	}
	catch (const std::string& e)
	{
		std::cerr << "[StaticMesh] :: " << e << std::endl;
	}


}

void Scene::Draw()
{
	// Render the Terrain
	// ==================
	_terrain->Draw(_fog);

	// Render the Ocean
	// ================
	//_ocean->Draw();

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
		_particuleSystem[i]->Draw();
	}

	//Render all Objects (Narratives & Usable)
	//========================================
	for (size_t i = 0; i < _objects.size(); i++)
	{
		_objects[i]->Draw();
	}

	// Render the Skybox
	// =================
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

void Scene::AddObject(const std::shared_ptr<Object>& object) {
	_objects.push_back(object);
}
