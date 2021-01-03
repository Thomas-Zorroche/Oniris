
#include "Panel.hpp"
#include "engine/Material.hpp"
#include "opengl/Mesh.hpp"


Panel::Panel(const std::string& texture, const std::string& name, float x, float y, float scale, int spriteSize, int nbSprite, bool visibility):
	_modelMatrix(glm::mat4(1.0f)), _nbSprite(nbSprite), _name(name), _visibility(visibility)
{
	float imgWidth = 0.0f, imgHeight = 0.0f;
	try {
		imgWidth = ResourceManager::Get().LoadTexture(texture, DIFFUSE).Width();
		imgHeight = ResourceManager::Get().LoadTexture(texture, DIFFUSE).Height();
	}
	catch (const std::string& e) {
		std::cerr << e << std::endl;
	}

	float posX = (imgWidth / float(_nbSprite)) / 1280.0 ;
	float posY = imgHeight / 720.0;
	_spriteSize = spriteSize / imgWidth;

	std::vector<ShapeVertex> vertices = {
				// position								// normal				// texcoord
		ShapeVertex(glm::vec3(-posX, posY, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 0.0)),
		ShapeVertex(glm::vec3( posX, posY, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(_spriteSize, 0.0)),
		ShapeVertex(glm::vec3( posX,-posY, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(_spriteSize, 1.0)),
		ShapeVertex(glm::vec3(-posX,-posY, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec2(0.0, 1.0))
	};


	auto material = ResourceManager::Get().CacheBasicMaterial(name, texture);
	

	std::vector<unsigned int> indices = {
		0,1,3,
		1,3,2
	};

	Mesh newMesh = Mesh(vertices, material, indices);
	_mesh = std::make_shared<Mesh>(newMesh);

	ComputeModelMatrix(x,y,scale);
	_texTranslation = glm::vec2(0.0f);


}

void Panel::Draw() const {
	auto shader = ResourceManager::Get().GetShader("Ui");
	shader->Bind();
	shader->SetUniformMatrix4fv("uModelMatrix", _modelMatrix);
	shader->SetUniform2f("uTexTranslation", _texTranslation[0], _texTranslation[1]);

	_mesh->Draw(shader);
}

void Panel::ComputeModelMatrix(float x, float y, float scale)
{
	Scale(scale, scale);
	Translate(x, y);

}

void Panel::Scale(float x, float y)
{
	_modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, 1)) * _modelMatrix;
}

void Panel::Translate(float x, float y)
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 1)) * _modelMatrix;
}

void Panel::TranslateTexture(int dir)
{
	if (dir >= 0)
		_texTranslation = _texTranslation + glm::vec2(_spriteSize, 0.0f);
	else 
		_texTranslation = _texTranslation - glm::vec2(_spriteSize, 0.0f);
}