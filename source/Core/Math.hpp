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

	Vec2& operator +  (Vec2 &other);
	Vec2& operator += (Vec2 &other);
	Vec2& operator -  (Vec2 &other);
	Vec2& operator -= (Vec2 &other);

	f32 x;
	f32 y;
};

}

#endif // MATH