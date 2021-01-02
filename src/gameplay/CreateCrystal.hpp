#pragma once

#include <unordered_map>
#include <memory>
#include <random>
#include <chrono>
#include <vector>

#include "gameplay/Object.hpp"
#include "gameplay/UsableObject.hpp"
#include "engine/Terrain.hpp"
#include "gameplay/Game.hpp"

#include "glm/glm.hpp"


class CreateCrystal
{
public:
	CreateCrystal(std::unordered_map<std::string, std::shared_ptr<Object>>& objects, 
		const std::shared_ptr<Terrain>& terrain, const std::shared_ptr<Game>& game) 
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);

		Model model = Model("res/models/objects/crystal.obj");
		glm::vec3 position = glm::vec3();

		for (int i = 0; i < 4; i++)
		{
			std::uniform_real_distribution<float> uniformRealDistributionX(0.0f, _spawnZones[i][2]);
			std::uniform_real_distribution<float> uniformRealDistributionZ(0.0f, _spawnZones[i][3]);

			position.x = uniformRealDistributionX(generator) + _spawnZones[i][0];
			position.z = uniformRealDistributionZ(generator) + _spawnZones[i][1];
			position.y = terrain->GetHeightOfTerrain(position.x, position.z);

			_spawnCoord.push_back(position);

			std::shared_ptr<Object> object = std::make_shared<UsableObject>(model, position, "o_crystal_" + std::to_string(i), "crystal", game);
			objects.insert({ "o_crystal_" + std::to_string(i), object });
		}
	}

	const std::vector<glm::vec3>& GetSpawnPositions() const { return _spawnCoord; }


private:
						 //spawnzone parameters :  x, z, height, width
	std::vector<std::vector<int>> _spawnZones = { {300, 100, 200, 200},
												  {800, 500, 100, 300},
												  {200, 300, 200, 200},
												  {400, 600, 300, 100} };

	std::vector<glm::vec3> _spawnCoord;
};

