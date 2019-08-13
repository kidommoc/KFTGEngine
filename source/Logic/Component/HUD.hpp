#ifndef KFTG_HUD
#define KFTG_HUD

#include "../../Core/types.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Hud : public Component
{
	Hud (Entity e, Entity c);

	Hud& operator = (const Hud &other);
	bool operator == (const Hud &other);
	bool operator != (const Hud &other);

	Entity owner;
	Entity camera;
};

Hud::Hud (Entity e, Entity c)
	: Component (ComponentType::HUD), owner (e), camera (c)
{}

Hud& Hud::operator = (const Hud &other)
{
	owner = other.owner;
	camera = other.camera;
	return *this;
}

bool Hud::operator == (const Hud &other)
{ return owner == other.owner; }

bool Hud::operator != (const Hud &other)
{ return owner != other.owner; }

}

#endif // HUD