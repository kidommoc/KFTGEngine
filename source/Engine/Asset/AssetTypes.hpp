#pragma once

#include "../Core/string.hpp"
#include "../Core/types.hpp"

namespace KFTG
{

typedef string GUID;

struct Image
{
	struct Color
	{
		u8 red;
		u8 green;
		u8 blue;
		u8 alpha;
	};

	u16 width;
	u16 height;
	Color image[0];
};

struct Audio
{
};

class XML
{
public:

private:
};

}