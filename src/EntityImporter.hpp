#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ParticuleSystem.hpp"
#include "Terrain.hpp"
#include "Object.hpp"

class Fog;

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

	std::vector<std::shared_ptr<ParticuleSystem> > ParticuleSystems(const std::string& data, std::shared_ptr<Terrain>& terrain, 
		const std::shared_ptr<Fog>& fog) const;
	std::vector<std::shared_ptr<Object> > Objects(const std::string& data, std::shared_ptr<Terrain>& terrain) const;
	std::vector<std::shared_ptr<StaticMesh> > StaticMeshes() const;

private:
	EntityImporter() = default;
	~EntityImporter() = default;
};
