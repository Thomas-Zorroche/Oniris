#include <vector>
#include <memory>
#include <string>

#include "SpecialMesh.hpp"
#include "Terrain.hpp"


class Scene
{
public:
	Scene(const std::string& pathScene);
	~Scene();

	void Init(const std::string& pathScene);

	void Update();


private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);
	//void AddLight();

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	//Terrain _terrain;
};