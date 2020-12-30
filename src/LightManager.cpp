#include "LightManager.hpp"

#include <string>
#include <iostream>

#include "DirectionalLight.hpp"
#include "Renderer.hpp"
#include "PointLight.hpp"

void LightManager::SendUniforms(const std::shared_ptr<Shader>& shader)
{
	for (size_t i = 0; i < _lights.size(); i++)
	{
		if (_lights[i]->Type() == LightType::POINT)
		{
			shader->SetUniform3f("pointLight.ambient", _lights[i]->Ambient());
			shader->SetUniform3f("pointLight.diffuse", _lights[i]->Diffuse());
			shader->SetUniform3f("pointLight.specular", _lights[i]->Specular());
			std::vector<glm::vec3> data = _lights[i]->GetSpecialData();
			glm::vec3 position = glm::vec3(Renderer::Get().View() * glm::vec4(_lights[i]->GetSpecialData()[0], 1));
			shader->SetUniform3f("pointLight.position", position);
			shader->SetUniform1f("pointLight.constant", 1.0f);
			shader->SetUniform1f("pointLight.linear", data[1].y);
			shader->SetUniform1f("pointLight.quadratic", data[1].z);
		}
		else if (_lights[i]->Type() == LightType::DIR)
		{
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