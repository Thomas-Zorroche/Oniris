#include "Scene.hpp"
#include "ResourceManager.hpp"
#include "EntityImporter.hpp"
#include "Terrain.hpp"
#include "Shader.h"
#include "Renderer.hpp"
#include "Ocean.hpp"
#include "Skybox.hpp"
#include "ParticuleSystem.hpp"
#include "stb_image.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>


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

	// Load all Shaders
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Terrain.frag", "Terrain");
	ResourceManager::Get().LoadShader("res/shaders/Ocean.vert", "res/shaders/Ocean.frag", "Ocean");
	ResourceManager::Get().LoadShader("res/shaders/Skybox.vert", "res/shaders/Skybox.frag", "Skybox");

	// Create Terrain
	_terrain = std::make_shared<Terrain>(0, 0, "res/img/grass_diffuse.jpg", "res/img/heightmap16.png");

	// Create Ocean
	_ocean = std::make_shared<Ocean>();

	// Create Skybox
	std::vector<std::string> facesSkybox
	{
		"res/img/skybox/test/right.jpg",
		"res/img/skybox/test/left.jpg",
		"res/img/skybox/test/top.jpg",
		"res/img/skybox/test/bottom.jpg",
		"res/img/skybox/test/front.jpg",
		"res/img/skybox/test/back.jpg"
	};
	//_skybox = std::make_shared<Skybox>(facesSkybox);
	
	// Particule Systems
	auto _particuleSystem = EntityImporter::Get().ParticuleSystems("res/scene/particule_systems.txt", _terrain);
	for (size_t i = 0; i < _particuleSystem.size(); i++)
	{
		AddParticuleSystem(_particuleSystem[i]);
	}

	// --------------------------------------------------
	// TEST SKYBOX
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < facesSkybox.size(); i++)
	{
		unsigned char* data = stbi_load(facesSkybox[i].c_str(), &width, &height, &nrChannels, 4);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << facesSkybox[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	_idSky = textureID;

	unsigned int skyboxVBO;
	glGenVertexArrays(1, &_VAOSky);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(_VAOSky);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// --------------------------------------------------


	//ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/Trees.frag", "Trees");
	//Model m_tree("res/models/trees/Sapin_01.obj");
	//AddStaticMesh(std::make_shared<StaticMesh>(m_tree, glm::vec3(250, _terrain->GetHeightOfTerrain(250, 250), 250), "Trees"));

	//ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Portail");
	//Model m_portail("res/models/portail/portail.obj");
	//AddStaticMesh(std::make_shared<StaticMesh>(m_portail, glm::vec3(350, _terrain->GetHeightOfTerrain(250, 250), 250), "Portail"));
}

void Scene::Draw()
{
	// Render the Skybox
	//_skybox->Draw();


	// Render the Terrain
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), _terrain->GetShader());
	Renderer::Get().SendBlinnPhongUniforms(_terrain->GetShader());
	//_terrain->Draw();

	// Render the Ocean
	//_ocean->Draw();

	// Render all the static meshes
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		//Renderer::Get().SendModelMatrixUniforms(_staticMeshes[i]->GetModelMatrix(), _staticMeshes[i]->GetShader());
		//_staticMeshes[i]->Draw();
	}

	// Render all the particule systems
	
	for (size_t i = 0; i < _particuleSystemCount; i++)
	{
		//_particuleSystem[i]->Draw();
	}

	// --------------------------------------------------
	// TEST SKYBOX
	glDepthFunc(GL_LEQUAL);
	auto shader = ResourceManager::Get().GetShader("Skybox");
	shader->Bind();
	glUniform1i(glGetUniformLocation(shader->getID(), "skybox"), 0);
	Renderer::Get().SendModelMatrixUniforms(glm::mat4(1.0f), shader, false);
	glBindVertexArray(_VAOSky);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _idSky);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
	// --------------------------------------------------

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

