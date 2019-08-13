#ifndef KFTG_MATH
#define KFTG_MATH

#include "types.hpp"
#include "string.hpp"

namespace KFTG
{

// hash: one_at_a_time
u32 hash (const string &key);

struct Vec2
{
	Vec2 (f32 a, f32 b) : x (a), y (b) {}

	bool  operator == (const Vec2 &other)
	{ return x == other.x && y == other.y; }

	bool  operator != (const Vec2 &other)
	{ return *this == other; }

	Vec2& operator +  (const Vec2 &other);
	Vec2& operator += (const Vec2 &other);
	Vec2& operator -  (const Vec2 &other);
	Vec2& operator -= (const Vec2 &other);

	f32 x;
	f32 y;
};

}

#endif // MATH