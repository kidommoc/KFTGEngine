#pragma once

#include <stdint.h>

namespace KFTG
{

// integer
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

// real
typedef float f32;

struct Color
{
	Color () : Color (0, 0, 0, 255) {}
	Color (u8 r, u8 g, u8 b, u8 a)
		: red (r), green (g), blue (b), alpha (a)
	{}

	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

}