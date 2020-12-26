 #pragma once
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <memory>

#include "ResourceManager.hpp"
#include "Mesh.hpp"
#include "common.hpp"
#include "Material.hpp"
#include "Shader.h"
#include "Renderer.hpp"

class Fog;

class Skybox
{
public:
	Skybox(const std::vector<std::string>& faces);

	void GenerateMesh();


	void Draw(const std::shared_ptr<Fog>& fog);

private:
	void SendUniforms(const std::shared_ptr<Fog>& fog);

	std::vector<std::string> _faces;
	unsigned int _id;
	std::shared_ptr<Shader> _shader;
	std::shared_ptr<Mesh> _mesh;

	static const float _SkyboxVertices[];

};