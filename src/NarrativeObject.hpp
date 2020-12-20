#pragma once
#include "Object.hpp"

enum NarrativebjectType
{
	TEXT,
	MODEL,
	SOUND
};

class NarrativeObject : public Object
{
public:
	NarrativeObject(const Model& model, glm::vec3 position, CollisionLayout cLayout);
	~NarrativeObject();

	void Read();

	static void FunctionTest() {
		std::cout << "HIT NARRATIVE OBJ \n";
	}

private:
	NarrativebjectType _Type = TEXT;

	bool IsText() { return (_Type == TEXT); }

};