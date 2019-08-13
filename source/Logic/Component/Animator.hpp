#ifndef KFTG_ANIMATION
#define KFTG_ANIMATION

#include "../../Core/types.hpp"
#include "../../Core/array.hpp"
#include "../../Core/Asset/AssetTypes.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Animator : public Component
{
	Animator (Entity e);

	Animator& operator = (const Animator &other);
	bool operator == (Animator &other);
	bool operator != (Animator &other);

	Entity owner;
	array<Animation*> ani;
};

Animator::Animator (Entity e)
	: Component (ComponentType::ANIMATOR), owner (e)
{}

Animator& Animator::operator = (const Animator &other)
{
	owner = other.owner;
	ani = other.ani;
	return *this;
}

bool Animator::operator == (Animator &other)
{
	return owner == other.owner;
}

bool Animator::operator != (Animator &other)
{
	return owner != other.owner;
}

}

#endif // SPRITE