#pragma once
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "FreeflyCamera.hpp"

#include "SpecialMesh.hpp"
#include "Shader.h"
#include "Terrain.hpp"
#include "ResourceManager.hpp"

#include <vector>
#include <memory>


class Renderer
{
public:
	static Renderer& Get()
	{
		static Renderer instance;
		return instance;
	}

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;


	void ComputeViewMatrix()
	{
		_view = _camera->getViewMatrix();
	}

	void ComputeProjectionMatrix()
	{
		float fov = _camera->GetFov();
		float ratio = _camera->GetWidth() / _camera->GetHeight();
		float nearPlane = _camera->GetNearPlane();
		float farPlane = _camera->GetFarPlane();
		
		_projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
	}

	void SendModelMatrixUniforms(const glm::mat4 & modelMatrix, std::shared_ptr<Shader>& shader) const
	{
		shader->Bind();

		glm::mat4 MVP = _projection * _view * modelMatrix;
		glm::mat4 MV = _view * modelMatrix;
		glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

		shader->SetUniformMatrix4fv("uMVPMatrix", MVP);
		shader->SetUniformMatrix4fv("uMVMatrix", MV);
		shader->SetUniformMatrix4fv("uNormalMatrix", NormalMatrix);

		shader->Unbind();
	}

	void SendBlinnPhongUniforms(std::shared_ptr<Shader>& shader) const
	{
		shader->Bind();

		glm::mat4 modelLight = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 0), glm::vec3(0, 1, 0));
		glm::vec4 LightDirection = _view * modelLight * glm::vec4(1, 1, 1, 0);

		shader->SetUniform3f("u_LightDir_vs", LightDirection.x, LightDirection.y, LightDirection.z);
		shader->SetUniform3f("u_LightIntensity", 1.0, 1.0, 1.0);
		shader->SetUniform3f("u_Kd", 1.0, 1.0, 1.0);
		shader->SetUniform3f("u_Ks", 1.0, 1.0, 1.0);
		shader->SetUniform1f("u_Shininess", 16.0);

		shader->Unbind();
	}

	void SetCamera(FreeflyCamera* camera)
	{
		_camera = camera;
	}


private:
	Renderer() = default;
	~Renderer() = default;

	FreeflyCamera* _camera;
	glm::mat4 _projection;
	glm::mat4 _view;
};