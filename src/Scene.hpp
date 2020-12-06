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

	void Draw();

	std::shared_ptr<Terrain>& TerrainPtr() { return _terrain; }
	std::shared_ptr<StaticMesh>& StaticMeshPtr(int index) { return _staticMeshes[index]; }

	int StaticMeshesCount() const { return _staticMeshesCount; }


private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);
	//void AddLight();

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	std::shared_ptr<Terrain> _terrain;

	unsigned int _staticMeshesCount = 0;
};