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
	u8 red;
	u8 green;
	u8 blue;
	u8 alpha;
};

}