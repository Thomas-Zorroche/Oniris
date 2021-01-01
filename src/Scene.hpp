#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Hud.hpp"
#include "glm/glm.hpp"

class Object;
class Ocean;
class ParticuleSystem;
class StaticMesh;
class Skybox;
class Terrain;
class Fog;
class Portal;


class Scene
{
public:
	Scene(const std::string& pathScene);
	~Scene();

	void Init(const std::string& pathScene);

	void Draw();

	std::shared_ptr<Terrain>& TerrainPtr() { return _terrain; }
	std::shared_ptr<StaticMesh>& StaticMeshPtr(int index) { return _staticMeshes[index]; }

	int StaticMeshesCount() const { return _staticMeshesCount; }

private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);
	void AddParticuleSystem(const std::shared_ptr<ParticuleSystem>& particuleSystem);
	//void AddObject(const std::string& name, const std::shared_ptr<Object>& object);
	//void AddLight();

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	std::vector<std::shared_ptr<ParticuleSystem> > _particuleSystem;
	std::unordered_map<std::string, std::shared_ptr<Object>> _objects;
	std::shared_ptr<Terrain> _terrain;
	std::shared_ptr<Ocean> _ocean;
	std::shared_ptr<Skybox> _skybox;
	std::shared_ptr<Fog> _fog;
	std::shared_ptr<Portal> _portal;

	unsigned int _staticMeshesCount = 0;
	unsigned int _particuleSystemCount = 0;



};

