#ifndef KFTG_ENTITY
#define KFTG_ENTITY

#include "../../Core/types.hpp"

namespace KFTG
{

struct Entity
{
	Entity () {}
	Entity (u16 n) : id (n) {}

	bool operator == (Entity &other) { return id == other.id; }
	bool operator != (Entity &other) { return id != other.id; }

	u16 id;
};

}

#endif // ENTITY