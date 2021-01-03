#include "lighting/LightManager.hpp"

#include <string>
#include <iostream>

#include "lighting/DirectionalLight.hpp"
#include "engine/Renderer.hpp"
#include "lighting/PointLight.hpp"
#include "engine/Terrain.hpp"
#include "gameplay/Portal.hpp"

const int LightManager::POINT_LIGHTS_COUNT = 7;

void LightManager::SendUniforms(const std::shared_ptr<Shader>& shader)
{
	int indexPointLights = 0;

	for (size_t i = 0; i < _lights.size(); i++)
	{

		if (_lights[i]->Type() == LightType::POINT)
		{
			std::string n = std::to_string(indexPointLights);

			if (indexPointLights > POINT_LIGHTS_COUNT)
				throw std::string("Can't have more than " + std::to_string(indexPointLights - 1) + " on the scene.");

			if (_lightsOn && _lights[i]->Electricity())
				shader->SetUniform1f("pointLights["+n+"].intensity", _lights[i]->Intensity());
			else if (!_lightsOn && _lights[i]->Electricity())
				shader->SetUniform1f("pointLights["+n+"].intensity", 0.0f);
			else if (!_lights[i]->Electricity())
				shader->SetUniform1f("pointLights["+n+"].intensity", _lights[i]->Intensity());

			shader->SetUniform3f("pointLights["+n+"].ambient", _lights[i]->Ambient());
			shader->SetUniform3f("pointLights["+n+"].diffuse", _lights[i]->Diffuse());
			shader->SetUniform3f("pointLights["+n+"].specular", _lights[i]->Specular());
			std::vector<glm::vec3> data = _lights[i]->GetSpecialData();
			glm::vec3 position = glm::vec3(Renderer::Get().View() * glm::vec4(_lights[i]->GetSpecialData()[0], 1));
			shader->SetUniform3f("pointLights["+n+"].position", position);
			shader->SetUniform1f("pointLights["+n+"].constant", 1.0f);
			shader->SetUniform1f("pointLights["+n+"].linear", data[1].y);
			shader->SetUniform1f("pointLights["+n+"].quadratic", data[1].z);

			indexPointLights++;
		}
		else if (_lights[i]->Type() == LightType::DIR)
		{
			if (_lightsOn)
				shader->SetUniform1f("dirLight.intensity", _lights[i]->Intensity());
			else
				shader->SetUniform1f("dirLight.intensity", 0.0f);
			
			shader->SetUniform3f("dirLight.ambient", _lights[i]->Ambient());
			shader->SetUniform3f("dirLight.diffuse", _lights[i]->Diffuse());
			shader->SetUniform3f("dirLight.specular", _lights[i]->Specular());
			glm::mat4 modelLight = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 0), glm::vec3(0, 1, 0));
			glm::vec4 LightDirection = Renderer::Get().View() * modelLight * glm::vec4(1, 1, 1, 0);
			shader->SetUniform3f("dirLight.direction", LightDirection.x, LightDirection.y, LightDirection.z);
		}
	}
}


void LightManager::AddLight(const BaseLightPtr& light, LightType type)
{
	if (type == LightType::POINT)
	{
		AddPointLight(light);
	}
	else if (type == LightType::DIR)
	{
		try
		{
			AddDirLight(light);
		}
		catch (const std::string& e)
		{
			std::cerr << e << std::endl;
		}
	}
}

void LightManager::AddPointLight(const BaseLightPtr& light)
{
	_lights.push_back(light);
	_pointLightsCount++;
}

void LightManager::AddDirLight(const BaseLightPtr& light)
{
	if (_dirLightsCount == 0)
	{
		_lights.push_back(light);
		_dirLightsCount++;
	}
	else
	{
		throw std::string("Cannot have more than one directional light in the scene.");
	}
}

void LightManager::SwitchLights()
{
	if (_lightsOn)
		_lightsOn = false;
	else
		_lightsOn = true;
}

void LightManager::LoadAllLights(const std::shared_ptr<Terrain>& terrain, const std::shared_ptr<Portal>& portal, const CreateCrystal& crystal)
{
	// Directional Light
	// =========================================================================
	std::shared_ptr<BaseLight> dirLight = std::make_shared<DirectionalLight>(
		1.0f,
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(1, 1, 1));

	// Point Lights Electricity (Village & Labo)
	// =========================================================================
	std::shared_ptr<BaseLight> pointLightVillage = std::make_shared<PointLight>(
		10.0f,
		glm::vec3(1, 0.6, 0),
		glm::vec3(604, terrain->GetHeightOfTerrain(604, 204), 204),
		325.0f);
	std::shared_ptr<BaseLight> pointLightLabo = std::make_shared<PointLight>(
		50.0f,
		glm::vec3(0, 0.6, 1),
		glm::vec3(850, terrain->GetHeightOfTerrain(850, 407) + 20, 407),
		160.0f);

	// Point Light Portal
	// =========================================================================
	std::shared_ptr<BaseLight> pointLightPortail = std::make_shared<PointLight>(
		0.0f,
		glm::vec3(0, 0.6, 1),
		glm::vec3(499, terrain->GetHeightOfTerrain(499, 578) + 10, 578),
		160.0f,
		false);

	// Point Light Crystal
	// =========================================================================
	auto crystalPositions = crystal.GetSpawnPositions();
	for (size_t i = 0; i < 4; i++)
	{
		std::shared_ptr<BaseLight> pointLightCrystal = std::make_shared<PointLight>(
			4.0f,
			glm::vec3(0.4, 0.4, 1.0),
			glm::vec3(crystalPositions[i].x, crystalPositions[i].y + 5, crystalPositions[i].z),
			100.0f,
			false);
		AddLight(pointLightCrystal, LightType::POINT);
	}


	AddLight(dirLight, LightType::DIR);
	AddLight(pointLightVillage, LightType::POINT);
	AddLight(pointLightLabo, LightType::POINT);
	AddLight(pointLightPortail, LightType::POINT);

	portal->SetLight(pointLightPortail);
}
