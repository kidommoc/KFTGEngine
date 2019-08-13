#ifndef KFTG_TRANSFORM
#define KFTG_TRANSFORM

#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Transform : public Component
{
	Transform (Entity e);
	Transform (Entity e, Transform *p);

	Transform& operator = (const Transform &other);
	bool operator == (const Transform &other);
	bool operator != (const Transform &other);

	Entity owner;
	Vec2 pos;
	Transform *parent;
};

Transform::Transform (Entity e) : Transform (e, nullptr)
{}

Transform::Transform (Entity e, Transform *p)
	: Component (ComponentType::TRANSFORM),
	owner (e), pos (0.0f, 0.0f), parent (p)
{}

Transform& Transform::operator = (const Transform &other)
{
	owner = other.owner;
	pos = other.pos;
	parent = other.parent;
	return *this;
}

bool Transform::operator == (const Transform &other)
{
	return owner == other.owner;
}

bool Transform::operator != (const Transform &other)
{
	return owner != other.owner;
}

}

#endif // TRANSFORM