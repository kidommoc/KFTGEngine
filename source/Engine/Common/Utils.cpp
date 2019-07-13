#include "Utils.hpp"

namespace KFTG
{

void memcpy (char *dest, const char *from, u32 len)
{
	for (u32 i = 0; i < len; ++i)
		dest[i] = from[i];
}

}