#pragma once

#include <vector>
#include <memory>
#include <string>

#include "SpecialMesh.hpp"
#include "Terrain.hpp"
#include "Ocean.hpp"
#include "ParticuleSystem.hpp"


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
	//void AddLight();

private:
	std::vector<std::shared_ptr<StaticMesh> > _staticMeshes;
	std::vector<std::shared_ptr<ParticuleSystem> > _particuleSystem;
	std::shared_ptr<Terrain> _terrain;
	std::shared_ptr<Ocean> _ocean;

	unsigned int _staticMeshesCount = 0;
	unsigned int _particuleSystemCount = 0;
};