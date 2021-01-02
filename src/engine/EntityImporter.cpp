#include "engine/EntityImporter.hpp"
#include "engine/ParticuleSystem.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Terrain.hpp"
#include "engine/StaticMesh.hpp"
#include "engine/Model.hpp"
#include "opengl/Shader.h"
#include "engine/Fog.hpp"
#include "gameplay/NarrativeObject.hpp"
#include "gameplay/UsableObject.hpp"
#include "gameplay/IOLight.hpp"
#include "gameplay/IODoor.hpp"
#include "hud/Panel.hpp"
#include "hud/Hud.hpp"

#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>



/*
* IMPORT PARTICULES SYSTEMS
*/
std::vector<std::shared_ptr<ParticuleSystem> > EntityImporter::ParticuleSystems(const std::string& filepath, 
	const std::shared_ptr<Terrain>& terrain, const std::shared_ptr<Fog>& fog) const
{
	std::vector<std::shared_ptr<ParticuleSystem> > particuleSystems;
	std::vector<ControlPointParticule> controlPoints;

	std::ifstream stream(filepath);
	std::string line;
	bool firstline = true;

	std::string name;
	std::string objPath;
	int count = 10;
	float size = 1.0f;
	float randomSize = 0.0f;
	bool alpha = false;

	while (getline(stream, line))
	{
		if (line.find("#ParticuleSystem") == std::string::npos && firstline)
		{
			// Wrong type data file, return empty vector
			std::cout << "[ENTITY IMPORTER] :: Wrong data file for : Particule System" << std::endl;
			return particuleSystems;
		}
		firstline = false;

		if (line.find("[name]") != std::string::npos)
		{
			name = line.substr(std::string("[name]").length() + 1);
		}

		if (line.find("[obj]") != std::string::npos)
		{
			objPath = line.substr(std::string("[obj]").length() + 1);
		}

		if (line.find("[alpha]") != std::string::npos)
		{
			alpha = std::stoi(line.substr(std::string("[alpha]").length() + 1));
		}

		if (line.find("[count]") != std::string::npos)
		{
			count = std::stoi(line.substr(std::string("[count]").length() + 1));
		}

		if (line.find("[size]") != std::string::npos)
		{
			line.erase(0, std::string("[size]").length() + 1);
			std::string delimiter = " ";

			// Retrieve first scale
			size_t pos = line.find(delimiter);
			std::string token = line.substr(0, pos);
			size = std::stof(token);
			line.erase(0, pos + delimiter.length());
			// Retrieve second scale
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			randomSize = std::stof(token);
		}

		if (line.find("[cp]") != std::string::npos)
		{
			line.erase(0, std::string("[cp]").length() + 1);
			
			glm::vec2 position;
			int density = 1;
			float radius = 10.0;
			
			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;
			for (size_t i = 0; i < 4; i++)
			{
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				switch (i)
				{
				case 0:
					position.x = std::stoi(token);
					break;
				case 1:
					position.y = std::stoi(token);
					break;
				case 2:
					density = std::stoi(token);
					break;
				case 3:
					radius = (float)std::stoi(token);
					break;
				}
				line.erase(0, pos + delimiter.length());
			}

			controlPoints.push_back(ControlPointParticule(position, density, radius));
		}

		if (line.find("[end]") != std::string::npos)
		{
			Model model = Model(objPath);
			TransformLayout transLayout(glm::vec3(0, terrain->GetHeightOfTerrain(0, 0), 0));

			if (alpha)
			{
				StaticMesh staticMesh = StaticMesh(model, transLayout, "ParticuleAlpha", fog);
				particuleSystems.push_back(std::make_shared<ParticuleSystem>(ParticuleSystem(name, staticMesh, count, size, randomSize, controlPoints, terrain)));
			}
			else
			{
				StaticMesh staticMesh = StaticMesh(model, transLayout, "Particule", fog);
				particuleSystems.push_back(std::make_shared<ParticuleSystem>(ParticuleSystem(name, staticMesh, count, size, randomSize, controlPoints, terrain)));
			}

			name = "";
			objPath = "";
			count = 0;
			size = 0.0f;
			alpha = false;
			randomSize = 0.0f;
			//controlPoints.clear();
		}
			
	}
	// End while loop

	return particuleSystems;
}

/*
* IMPORT STATIC MESHES
*/
std::vector<std::shared_ptr<StaticMesh> > EntityImporter::StaticMeshes(const std::string& filepath, const std::shared_ptr<Terrain>& terrain,
	const std::shared_ptr<Fog>& fog) const
{
	std::vector<std::shared_ptr<StaticMesh> > staticMeshes;

	std::ifstream stream(filepath);
	std::string line;
	bool firstline = true;

	// Data to fill
	std::string objPath;
	glm::vec2 location(0.0f, 0.0f);
	glm::vec3 rotation(0, 0, 0);
	float scale = 1.0f;

	while (getline(stream, line))
	{
		if (line.find("#StaticMeshes") == std::string::npos && firstline)
		{
			// Wrong type data file, return empty vector
			std::cout << "[ENTITY IMPORTER] :: Wrong data file for : Static Meshes" << std::endl;
			return staticMeshes;
		}
		firstline = false;

		if (line.find("[obj]") != std::string::npos)
		{
			objPath = line.substr(std::string("[obj]").length() + 1);
		}

		if (line.find("[rot]") != std::string::npos)
		{
			line.erase(0, std::string("[rot]").length() + 1);
			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;

			for (size_t i = 0; i < 3; i++)
			{
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				rotation[i] = std::stof(token);

				line.erase(0, pos + delimiter.length());
			}
		}

		if (line.find("[scl]") != std::string::npos)
		{
			scale = std::stof(line.substr(std::string("[scl]").length() + 1));
		}

		if (line.find("[loc]") != std::string::npos)
		{
			line.erase(0, std::string("[loc]").length() + 1);
			std::string delimiter = " ";

			// Retrieve X Coord
			size_t pos = line.find(delimiter);
			std::string token = line.substr(0, pos);
			location.x = std::stof(token);
			line.erase(0, pos + delimiter.length());
			// Retrieve Z Coord
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			location.y = std::stof(token);
		}


		if (line.find("[end]") != std::string::npos)
		{
			Model model(objPath);
			CollisionLayout cLayout(true, true, false);
			TransformLayout transLayout(glm::vec3(location.x, terrain->GetHeightOfTerrain(location.x, location.y), location.y),
				rotation, scale);

			staticMeshes.push_back(std::make_shared<StaticMesh>(model, transLayout, "Model3D_Tex", fog, cLayout));
			
			/*
			* Variadic fonction pour remettre les parametre par defaut ?
			*/
			objPath = "";
			location = glm::vec2(0.0f, 0.0f);
			rotation = glm::vec3(0, 0, 0);
			scale = 1.0f;
		}

	}
	// End while loop

	return staticMeshes;
}

/*
* IMPORT OBJECTS
*/
ObjectArrayImporter EntityImporter::Objects(const std::string& filepath, const std::shared_ptr<Terrain>& terrain,
	const std::shared_ptr<Fog>& fog, const std::shared_ptr<Game>& game) const {

	// Return values
	std::unordered_map<std::string, std::shared_ptr<Object>> objects;
	std::vector<std::shared_ptr<StaticMesh> > ioObjects;

	std::ifstream stream(filepath);
	std::string line;
	bool firstline = true;

	std::string name;
	std::string type;
	std::string objPath;
	std::string texPath;
	glm::vec3 position = glm::vec3();
	int rotation = 0;
	std::string objPathIO;

	while (getline(stream, line))
	{
		if (line.find("#Objects") == std::string::npos && firstline)
		{
			// Wrong type data file, return empty vector
			std::cout << "[ENTITY IMPORTER] :: Wrong data file for : Object" << std::endl;
			return { objects, ioObjects };
		}
		firstline = false;

		if (line.find("[name]") != std::string::npos)
		{
			name = line.substr(std::string("[name]").length() + 1);
		}

		if (line.find("[type]") != std::string::npos)
		{
			type = line.substr(std::string("[type]").length() + 1);
		}

		if (line.find("[obj]") != std::string::npos)
		{
			objPath = line.substr(std::string("[obj]").length() + 1);
		}

		if (line.find("[objIO]") != std::string::npos)
		{
			objPathIO = line.substr(std::string("[objIO]").length() + 1);
		}

		if (line.find("[tex]") != std::string::npos)
		{
			texPath = line.substr(std::string("[tex]").length() + 1);
		}

		if (line.find("[rot]") != std::string::npos)
		{
			rotation = std::stof(line.substr(std::string("[scl]").length() + 1));
		}

		if (line.find("[pos]") != std::string::npos)
		{
			line.erase(0, std::string("[pos]").length() + 1);

			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;
			for (size_t i = 0; i < 2; i++)
			{
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				switch (i)
				{
				case 0:
					position.x = std::stof(token);
					break;
				case 1:
					position.z = std::stof(token);
					break;
				}
				line.erase(0, pos + delimiter.length());
			}
		}

		if (line.find("[end]") != std::string::npos)
		{
			Model model = Model(objPath);

			//
			// [ TO DO ] :: trie des shaders - quel shader mettre aux objects
			//
			position.y = terrain->GetHeightOfTerrain(position.x, position.z);
			std::shared_ptr<Object> object = nullptr;
			if (type == "Um") 
				object = std::make_shared<UsableObject>(model, position, "o_" + name, "map", game);
			else if (type == "Uk") 
				object = std::make_shared<UsableObject>(model, position, "o_" + name, "key", game);
			else if (type == "N")
			{
				Panel panel = Panel(texPath, "o_" + name, 0.4, 0, 1, 512, 1, false);
				Hud::Get().AddPanel("o_" + name, std::make_shared<Panel>(panel));
				object = std::make_shared<NarrativeObject>(model, position, "o_" + name);
			}
			else if (type == "Il" || type == "Id")
			{
				CollisionLayout cLayout(true, true, false);
				TransformLayout transLayout(position, glm::vec3(0, rotation, 0));
				auto ioObjectPtr = std::make_shared<StaticMesh>(Model(objPathIO), transLayout, "Model3D_Tex", fog, cLayout);
				ioObjects.push_back(ioObjectPtr);
				if (type == "Il")
					object = std::make_shared<IOLight>(model, transLayout, "p_lightup", ioObjectPtr);
				else
					object = std::make_shared<IODoor>(model, transLayout, "p_open", ioObjectPtr);
			}	

				
			objects.insert({ name, object });

			// clear data :
			name = "";
			type = "";
			objPath = "";
			texPath = "";
			position = glm::vec3();
			objPathIO = "";
			rotation = 0;
		}

	}
	// End while loop


	return { objects, ioObjects };
}




