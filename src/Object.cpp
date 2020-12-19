#include "Object.hpp"
#include "ResourceManager.hpp"

Object::Object(const std::string& path, const std::shared_ptr<Terrain>& terrain) {
	Model model("res/models" + path );
	ResourceManager::Get().LoadShader("res/shaders/3DTex.vert", "res/shaders/model.frag", "Key");

	_Mesh = std::make_shared<StaticMesh>(model, glm::vec3(250, terrain->GetHeightOfTerrain(250, 250), 250), "Key");
}

Object::~Object() {

}

void Object::Draw() {
	_Mesh->Draw();
}