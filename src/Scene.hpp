#pragma once

#include <vector>
#include <memory>
#include <string>

#include "StaticMesh.hpp"
#include "Terrain.hpp"
#include "Hud.hpp"
#include "Ocean.hpp"
#include "Skybox.hpp"
#include "ParticuleSystem.hpp"
#include "Object.hpp"


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
	Hud& GetHud() { return _hud; }


private:
	void AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh);
	void AddParticuleSystem(const std::shared_ptr<ParticuleSystem>& particuleSystem);
	void AddObject(const std::shared_ptr<Object>& object);
	//void AddLight();

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	std::vector<std::shared_ptr<ParticuleSystem> > _particuleSystem;
	std::vector<std::shared_ptr<Object> > _objects;
	std::shared_ptr<Terrain> _terrain;
	Hud _hud;
	std::shared_ptr<Ocean> _ocean;
	std::shared_ptr<Skybox> _skybox;


	unsigned int _staticMeshesCount = 0;
	unsigned int _particuleSystemCount = 0;

	// VARIABLE TEST
	unsigned int _idSky = 0;
	unsigned int _VAOSky = 0;
};