#ifndef KFTG_COLLIDER
#define KFTG_COLLIDER

#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

enum ColliderType
{
};

struct Collider : public Component
{
	Collider (Entity e, ColliderType t);
	Collider (Entity e, ColliderType t, Vec2 lt, Vec2 rb);

	Collider& operator = (const Collider &other);
	bool operator == (const Collider &other);
	bool operator != (const Collider &other);

	Entity owner;
	ColliderType type;
	Vec2 leftTop;
	Vec2 rightBottom;
};

Collider::Collider (Entity e, ColliderType t)
	: Collider (e, t, {0.0f, 0.0f}, {0.0f, 0.0f}) 
{}

Collider::Collider (Entity e, ColliderType t, Vec2 lt, Vec2 rb)
	: Component (ComponentType::COLLIDER), owner (e), type (t),
	leftTop (lt), rightBottom (rb)
{}

Collider& Collider::operator = (const Collider &other)
{
	owner = other.owner;
	type = other.type;
	leftTop = other.leftTop;
	rightBottom = other.rightBottom;
	return *this;
}

bool Collider::operator == (const Collider &other)
{
	return owner == other.owner && type == other.type
		&& leftTop == other.leftTop && rightBottom == other.rightBottom;
}

bool Collider::operator != (const Collider &other)
{
	return !(*this == other);
}

}

#endif // MOTION