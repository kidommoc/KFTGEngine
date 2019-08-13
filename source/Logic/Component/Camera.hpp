#ifndef KFTG_CAMERA
#define KFTG_CAMERA

#include "../../Core/types.hpp"
#include "../../Core/Math.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

struct Camera : public Component
{
	Camera (Entity e);
	Camera (Entity e, Vec2 p, Vec2 s);

	Camera& operator = (const Camera &other);
	bool operator == (Camera &other);
	bool operator != (Camera &other);

	Entity owner;
	Vec2 pos;
	Vec2 size;
};

Camera::Camera (Entity e)
	: Camera (e, {0.0f, 0.0f}, {0.0f, 0.0f})
{}

Camera::Camera (Entity e, Vec2 p, Vec2 s)
	: Component (ComponentType::CAMERA), owner (e),
	pos (p), size (s)
{}

Camera& Camera::operator = (const Camera &other)
{
	owner = other.owner;
	pos = other.pos;
	size = other.size;
	return *this;
}

bool Camera::operator == (Camera &other)
{ return owner == other.owner; }

bool Camera::operator != (Camera &other)
{ return owner != other.owner; }

}

#endif // UI