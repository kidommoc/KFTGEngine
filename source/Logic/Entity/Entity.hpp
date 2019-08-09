#ifndef KFTG_ENTITY
#define KFTG_ENTITY

#include "../../Core/types.hpp"
#include "../World/World.hpp"

namespace KFTG
{

struct Entity
{
	Entity () {}
	Entity (u16 n) : id (n) {}
	u16 id;
};

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

#endif // ENTITY