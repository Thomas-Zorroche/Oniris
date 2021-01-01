 #pragma once
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <memory>

#include "engine/ResourceManager.hpp"
#include "opengl/Mesh.hpp"
#include "common.hpp"
#include "engine/Material.hpp"
#include "opengl/Shader.h"
#include "engine/Renderer.hpp"

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