#ifndef KFTG_COMPONENT
#define KFTG_COMPONENT

#include "../../Core/types.hpp"
#include "World.hpp"

#define COMPONENTS_NUM 16

namespace KFTG
{

enum ComponentType
{
	/*
	TRANSFORM,
	MOTION,
	CAMARA,
	JOYSTICK,
	ACTION,
	SPRITE,
	ANIMATION,
	COLLIDER
	*/
	/*
	TRANSFORM = 1,
	MOTION    = 2,
	CAMARA    = 4,
	JOYSTICK  = 8,
	ACTION    = 16,
	SPRITE    = 32,
	ANIMATION = 64,
	COLLIDER  = 128
	*/
};

// each component should inherit it and set its own mask

struct Component
{
	const u16 type;

	virtual bool operator == (Component &other) = 0;
	virtual bool operator != (Component &other) = 0;
};

template <typename ComponentType>
struct ComponentHandle
{
	Entity entity;
	ComponentType *component;

	ComponentHandle (Entity e);

	void destroy ()
	{ _world->removeComponent<ComponentType> (entity); }

private:
	World *_world;
	ComponentManager<ComponentType> *_manager;
};

class ComponentsMask
{
public:
	ComponentsMask () : mask (0) {}

	void add    (u16 m)
	{ mask |= 1 << (m - 1); }
	//{ mask |= m; }

	void remove (u16 m)
	{ mask &= ~(1 << (m - 1)); }
	//{ mask &= ~m; }

	bool query  (u16 m)
	{ return mask & (1 << m - 1); }
	//{ return mask & m; }

	bool match (u16 m)
	{ return mask && !m; }

	bool match (ComponentsMask &m)
	{ return mask && !m.mask; }

private:
	u16 mask;
};

}

#endif // COMPONENT