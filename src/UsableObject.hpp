#pragma once
#include "Object.hpp"

class UsableObject : public Object
{
public:
	UsableObject::UsableObject(const std::string& path, const std::shared_ptr<Terrain>& terrain);
	~UsableObject();
	
private:

};

