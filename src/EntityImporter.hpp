#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ParticuleSystem.hpp"
#include "Terrain.hpp"
#include "Object.hpp"

class Fog;

struct ObjectArrayImporter
{
	std::unordered_map<std::string, std::shared_ptr<Object>> objects;
	std::vector <std::shared_ptr<StaticMesh> > ioObjects;
};

class EntityImporter
{
public:
	static EntityImporter& Get()
	{
		static EntityImporter instance;
		return instance;
	}

	EntityImporter(const EntityImporter&) = delete;
	EntityImporter& operator=(const EntityImporter&) = delete;

	ObjectArrayImporter Objects(const std::string& data, std::shared_ptr<Terrain>& terrain,
		const std::shared_ptr<Fog>& fog) const;

	std::vector<std::shared_ptr<ParticuleSystem> > ParticuleSystems(const std::string& data, std::shared_ptr<Terrain>& terrain, 
		const std::shared_ptr<Fog>& fog) const;

	std::vector<std::shared_ptr<StaticMesh> > StaticMeshes(const std::string& data, std::shared_ptr<Terrain>& terrain,
		const std::shared_ptr<Fog>& fog) const;


private:
	EntityImporter() = default;
	~EntityImporter() = default;
};
