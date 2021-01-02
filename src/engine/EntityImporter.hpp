#pragma once

#include <string>
#include <vector>
#include <memory>
#include "engine/ParticuleSystem.hpp"
#include "engine/Terrain.hpp"
#include "gameplay/Object.hpp"

class Fog;
class Game;

struct ObjectArrayImporter
{
	std::unordered_map<std::string, std::shared_ptr<Object>> objects;
	std::vector <std::shared_ptr<StaticMesh> > ioObjects;
};

class EntityImporter
{
public:
	EntityImporter() = default;

	ObjectArrayImporter Objects(const std::string& data, const std::shared_ptr<Terrain>& terrain,
		const std::shared_ptr<Fog>& fog, const std::shared_ptr<Game>& game) const;

	std::vector<std::shared_ptr<ParticuleSystem> > ParticuleSystems(const std::string& data, const std::shared_ptr<Terrain>& terrain, 
		const std::shared_ptr<Fog>& fog) const;

	std::vector<std::shared_ptr<StaticMesh> > StaticMeshes(const std::string& data, const std::shared_ptr<Terrain>& terrain,
		const std::shared_ptr<Fog>& fog) const;

private:

};
