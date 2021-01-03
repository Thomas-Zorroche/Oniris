#pragma once

#include <vector>
#include <memory>
#include <string>
#include "hud/Hud.hpp"
#include "glm/glm.hpp"

class Object;
class Ocean;
class ParticuleSystem;
class StaticMesh;
class Skybox;
class Terrain;
class Fog;
class Portal;
class Game;

class Scene
{
public:
	Scene(const std::shared_ptr<Game>& game);
	~Scene();

	void Init(const std::shared_ptr<Game>& game);

	void Draw();

	std::shared_ptr<Terrain>& TerrainPtr() { return _terrain; }
	std::shared_ptr<StaticMesh>& StaticMeshPtr(int index) { return _staticMeshes[index]; }

	void Free();

private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);
	void AddParticuleSystem(const std::shared_ptr<ParticuleSystem>& particuleSystem);

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

