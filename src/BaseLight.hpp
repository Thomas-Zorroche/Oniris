#pragma once

#include "glm/glm.hpp"
#include <memory>

class BaseLight
{
public:
	BaseLight(float intensity = 1.0f, 
			  const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0));

	float Intensity() const;
	float SetIntensity(float intensity);

	const glm::vec3& Color() const;
	float SetColor(const glm::vec3& color);

	const glm::vec3& Position() const;
	float SetPosition(const glm::vec3& position);

	void Translate(const glm::vec3& delta);
	void Scale(float alpha);
	void Rotate(float alpha, const glm::vec3& axis);

private:
	unsigned int _id;

	float _intensity;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


	float radius;
	glm::mat4 _modelMatrix = glm::mat4(1.0f);
};

using BaseLightPtr = std::shared_ptr<BaseLight>;