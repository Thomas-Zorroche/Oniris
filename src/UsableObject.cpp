#include "UsableObject.hpp"
#include "ResourceManager.hpp"

UsableObject::UsableObject(const std::string& path, const std::shared_ptr<Terrain>& terrain)
	: Object(path, terrain)
{

}


UsableObject::~UsableObject() {};