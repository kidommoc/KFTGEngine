#ifndef KFTG_ENTITY_MANAGER
#define KFTG_ENTITY_MANAGER

#include "../../Core/types.hpp"
#include "../../Core/array.hpp"
#include "Entity.hpp"

namespace KFTG
{

class EntityManager
{
public:
	EntityManager ()
		: _entityCount (0), _entities ()
	{}
	~EntityManager ();

	Entity createEntity ();
	Entity createEntity (u16 pos);
	void destroyEntity (Entity e);

private:
	u16 _entityCount;
	array<Entity> _entities;
};

}

#endif // ENTITY_MANAGER