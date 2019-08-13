#include "Math.hpp"

namespace KFTG
{

u32 hash (const string &key)
{
	u32 h = 0;

	for (u32 i = 0; i < key.getLen (); ++i)
	{
		h += key[i];
		h += (h << 10);
		h ^= (h >> 6);
	}
	h += (h << 3);
	h ^= (h >> 11);
	h += (h << 15);
	return h;
}

Vec2& Vec2::operator + (const Vec2 &other)
{
	Vec2 v (x + other.x, y + other.y);
	return v;
}

Vec2& Vec2::operator += (const Vec2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vec2& Vec2::operator - (const Vec2 &other)
{
	Vec2 v (x - other.x, y - other.y);
	return v;
}

Vec2& Vec2::operator -= (const Vec2 &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

}