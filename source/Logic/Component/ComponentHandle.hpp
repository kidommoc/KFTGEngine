#ifndef KFTG_COMPONENT_HANDLE
#define KFTG_COMPONENT_HANDLE

#include "../../Core/types.hpp"
#include "ComponentManager.hpp"
#include "../World/World.hpp"

namespace KFTG
{

class World;

template <typename ComponentType>
struct ComponentHandle
{
	Entity entity;
	ComponentType *component;

	ComponentHandle (Entity e);

	void destroy ();

private:
	World *_world;
	ComponentManager<ComponentType> *_manager;
};

}

#endif // COMPONENT