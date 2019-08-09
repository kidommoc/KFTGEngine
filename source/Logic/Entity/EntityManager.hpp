#ifndef KFTG_ENTITY_MANAGER
#define KFTG_ENTITY_MANAGER

#include "../../Core/types.hpp"
#include "Entity.hpp"

namespace KFTG
{

class EntityManager
{
public:
	EntityManager () : entityCount (0) {}
	~EntityManager ();

	Entity createEntity ();
	void destroyEntity (Entity e);

private:
	u16 entityCount;
};

}

#endif // ENTITY_MANAGER