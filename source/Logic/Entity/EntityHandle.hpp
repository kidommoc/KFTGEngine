#ifndef KFTG_ENTITY_HANDLE
#define KFTG_ENTITY_HANDLE

#include "../../Core/types.hpp"
#include "Entity.hpp"
#include "../World/World.hpp"

namespace KFTG
{

class World;

struct EntityHandle
{
	Entity entity;

	EntityHandle (Entity e, World *w)
		: entity (e), _world (w)
	{}

	void destroy ();

	template <typename ComponentType>
	void addComponent (ComponentType &c);

	template <typename ComponentType>
	void removeComponent ();

private:
	World *_world;
};

}

#endif // ENTITY_HANDLE