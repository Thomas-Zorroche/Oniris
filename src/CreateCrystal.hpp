#pragma once

#include <unordered_map>
#include <memory>
#include <ctime>
#include <vector>

#include "Object.hpp"
#include "UsableObject.hpp"
#include "Terrain.hpp"
#include "Game.hpp"


class CreateCrystal
{
public:
	CreateCrystal(std::unordered_map<std::string, std::shared_ptr<Object>>& objects, 
		const std::shared_ptr<Terrain>& terrain, const std::shared_ptr<Game>& game) 
	{
		std::srand(std::time(nullptr));
		Model model = Model("res/models/objects/crystal.obj");
		glm::vec3 position = glm::vec3();

		for (int i = 0; i < 4; i++)
		{

			position.x = (std::rand() % _spawnZones[i][2]) + _spawnZones[i][0];
			position.z = (std::rand() % _spawnZones[i][3]) + _spawnZones[i][1];
			position.y = terrain->GetHeightOfTerrain(position.x, position.z);

			std::shared_ptr<Object> object = std::make_shared<UsableObject>(model, position, "o_crystal_" + std::to_string(i), "crystal", game);
			objects.insert({ "o_crystal_" + std::to_string(i), object });
			std::cout << position.x << " " << position.z << std::endl;
		}
	}


private:
						 //spawnzone parameters :  x, z, height, width
	std::vector<std::vector<int>> _spawnZones = { {300, 100, 200, 200},
												  {800, 500, 100, 300},
												  {200, 300, 200, 200},
												  {400, 600, 200, 100} };
};

