#ifndef KFTG_SYSTEM
#define KFTG_SYSTEM

#include "../../Core/array.hpp"
#include "../Entity/Entity.hpp"
#include "../Component/Component.hpp"
#include "../World/World.hpp"

namespace KFTG
{

class System
{
public:
	virtual void init () = 0;
	virtual void update (f32 deltaTime) = 0;
	
	void setWorld (World *w) { _world = w; }
	void registerEntity   (Entity e);
	void unregisterEntity (Entity e);
	ComponentsMask getMask () { return mask; }

protected:
	World *_world;
	ComponentsMask mask;
	array<Entity> _entities;
};

}

#endif // SYSTEM