#ifndef KFTG_MOTION
#define KFTG_MOTION

#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Motion : public Component
{
	Motion (Entity e);
	Motion (Entity e, Vec2 v, Vec2 a);

	Motion& operator = (const Motion &other);
	bool operator == (const Motion &other);
	bool operator != (const Motion &other);

	Entity owner;
	Vec2 velocity;
	Vec2 acceleration;
};

Motion::Motion (Entity e)
	: Motion (e, {0.0f, 0.0f}, {0.0f, 0.0f})
{}

Motion::Motion (Entity e, Vec2 v, Vec2 a)
	: Component (ComponentType::MOTION), owner (e), 
	velocity (v), acceleration (a)
{}

Motion& Motion::operator = (const Motion &other)
{
	owner = other.owner;
	velocity = other.velocity;
	acceleration = other.acceleration;
}

bool Motion::operator == (const Motion &other)
{
	return owner == other.owner;
}

bool Motion::operator != (const Motion &other)
{
	return owner != other.owner;
}

}

#endif // MOTION