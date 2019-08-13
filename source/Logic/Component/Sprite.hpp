#ifndef KFTG_SPRITE
#define KFTG_SPRITE

#include "../../Core/types.hpp"
#include "../../Core/Asset/AssetTypes.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Sprite : public Component
{
	Sprite (Entity e);
	Sprite (Entity e, Image *i);

	Sprite& operator = (const Sprite &other);
	bool operator == (const Sprite &other);
	bool operator != (const Sprite &other);

	Entity owner;
	Image *img;
};

Sprite::Sprite (Entity e)
	: Sprite (e, nullptr)
{}

Sprite::Sprite (Entity e, Image *i)
	: Component (ComponentType::SPRITE), owner (e), img (i)
{}

Sprite& Sprite::operator = (const Sprite &other)
{
	owner = other.owner;
	img = other.img;
	return *this;
}

bool Sprite::operator == (const Sprite &other)
{
	return owner == other.owner;
}

bool Sprite::operator != (const Sprite &other)
{
	return owner != other.owner;
}

}

#endif // SPRITE