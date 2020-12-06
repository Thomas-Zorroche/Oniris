#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "Terrain.hpp"
#include "Shader.h"

#include <memory>
#include <string>
#include <iostream>


Scene::Scene(const std::string& pathScene)
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


	// Create Static Meshes
}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
}
