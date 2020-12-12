
#include "Panel.hpp"
#include "Material.hpp"


Panel::Panel(const std::string texture, std::string name, float x, float y, float scale):
	_modelMatrix(glm::mat4(1.0f)), _name(name)
{
	//
	// [TODO] :: Global window size
	//

	float imgWidth = ResourceManager::Get().LoadTexture(texture, DIFFUSE).Width();
	float width = imgWidth / 1080.0;
	float imgHeight = ResourceManager::Get().LoadTexture(texture, DIFFUSE).Height();
	float height = imgHeight / 720.0;

	std::vector<ShapeVertex> vertices = {
				// position								// normal				// texcoord
		ShapeVertex(glm::vec3(-width, height, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0)),
		ShapeVertex(glm::vec3( width, height, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 0.0)),
		ShapeVertex(glm::vec3( width,-height, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(1.0, 1.0)),
		ShapeVertex(glm::vec3(-width,-height, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 1.0))
	};


	auto material = ResourceManager::Get().CacheBasicMaterial(_name, texture);
	

	std::vector<unsigned int> indices = {
		0,1,3,
		1,3,2
	};

	Mesh newMesh = Mesh(vertices, material, &indices);
	_mesh = std::make_shared<Mesh>(newMesh);

	ComputeModelMatrix(x,y,scale);

	
}


void Panel::Draw() {
	auto shader = ResourceManager::Get().GetShader("Ui");
	shader->Bind();
	shader->SetUniformMatrix4fv("uModelMatrix", _modelMatrix);
	
	_mesh->Draw(shader);
}

void Panel::ComputeModelMatrix(float x, float y, float scale)
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale,scale,scale));

}
