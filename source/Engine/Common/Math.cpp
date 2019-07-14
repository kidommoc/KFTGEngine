#include "Math.hpp"

namespace KFTG
{

u32 hash (string key)
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

}