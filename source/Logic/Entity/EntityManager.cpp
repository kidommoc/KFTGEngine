#include "EntityManager.hpp"

namespace KFTG
{

Entity EntityManager::createEntity ()
{
	Entity e;
	e.id = entityCount++;
	return e;
}

void EntityManager::destroyEntity ()
{
}


}