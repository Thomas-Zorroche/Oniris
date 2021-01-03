#pragma once
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "engine/Camera.hpp"

#include "engine/StaticMesh.hpp"
#include "opengl/Shader.h"
#include "engine/Terrain.hpp"
#include "engine/ResourceManager.hpp"

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

	void SendTransMatrixUniforms(const glm::mat4 & modelMatrix, std::shared_ptr<Shader>& shader, bool removeTranslationView = false)
	{
		if (removeTranslationView)
			_view = glm::mat4(glm::mat3(_view));

		glm::mat4 MVP = _projection * _view * modelMatrix;
		glm::mat4 MV = _view * modelMatrix;
		glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MV));

		shader->SetUniformMatrix4fv("uMVPMatrix", MVP);
		shader->SetUniformMatrix4fv("uMVMatrix", MV);
		shader->SetUniformMatrix4fv("uNormalMatrix", NormalMatrix);
		shader->SetUniformMatrix4fv("uModelMatrix", modelMatrix);
		shader->SetUniform3f("cameraPos", _camera->GetPosition());

		if (removeTranslationView)
			ComputeViewMatrix();
	}

	void SetCamera(const std::shared_ptr<Camera>& camera)
	{
		_camera = camera;
		ComputeProjectionMatrix();
	}

	glm::mat4 View() const { return _view;  }

private:
	Renderer() = default;
	~Renderer() = default;

	std::shared_ptr<Camera>  _camera;
	glm::mat4 _projection;
	glm::mat4 _view;
};