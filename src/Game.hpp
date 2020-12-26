#pragma once

class Game
{
public:
	static Game& Get()
	{
		static Game instance;
		return instance;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;


	void SetRefObjects(std::unordered_map<std::string, std::shared_ptr<Object>>* obj) { _objects = obj; }
	void PickUp(const std::string& type) { 
		if (type == "key")
			_HasKey = true;
		else if (type == "map")
			_HasMap = true;
		//_objects->erase(type);
	};

	void LostKey() { _HasKey = false; };
	bool HasKey() const { return _HasKey; };
	bool Hasmap() const { return _HasMap; };

private:

	Game() = default ;
	~Game() = default ;

	bool _HasKey = false;
	bool _HasMap = false;
	std::unordered_map<std::string, std::shared_ptr<Object>>* _objects = nullptr;
};
