#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Material.hpp"

#include <memory>
#include <string>
#include <iostream>
#include "glm/glm.hpp"


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

	//Create Ui
	ResourceManager::Get().LoadShader("res/shaders/3DTex_ui.vert", "res/shaders/model.frag", "Ui");
	Model m_ui("res/models/plan_ui/plan.obj");
	//AddStaticMesh(std::make_shared<StaticMesh>(m_ui, glm::vec3(250, _terrain->GetHeightOfTerrain(250, 250)+ 2.0, 250), "Ui"));

	//______________________________________________________________________________create mesh ui

	std::vector<ShapeVertex> vertices = {
						// position					// normal				// texcoord
		ShapeVertex(glm::vec3(-1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0)),
		ShapeVertex(glm::vec3( 1.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 1.0)),
		ShapeVertex(glm::vec3( 1.0,-1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 1.0)),
		ShapeVertex(glm::vec3(-1.0,-1.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0))

	};

	//const auto material = ResourceManager::Get().CachePBRColorMaterial("ui", glm::vec3(1.0, 1.0, 1.0));
	const auto material = ResourceManager::Get().CacheBasicMaterial("ui", "res/img/uiplaceholder.png");

	std::vector<unsigned int> indices = {
		0,1,3,
		1,3,2
	};

	Mesh newMesh = Mesh(vertices, material, &indices);
	_mesh = std::make_shared<Mesh>(newMesh);


	//______________________________________________________________________________________________

	//AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(250, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
//	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(350, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
//	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(450, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
//	AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(650, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
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


	_mesh->Draw(ResourceManager::Get().GetShader("Ui"));

}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
	_staticMeshesCount++;
}
