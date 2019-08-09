#ifndef KFTG_ENTITY
#define KFTG_ENTITY

#include "../../Core/types.hpp"

namespace KFTG
{

struct Entity
{
	Entity () {}
	Entity (u16 n) : id (n) {}
	u16 id;
};

}

#endif // ENTITY