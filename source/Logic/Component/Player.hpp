#ifndef KFTG_PLAYER
#define KFTG_PLAYER

#include "../../Core/types.hpp"
#include "../Entity/Entity.hpp"
#include "Component.hpp"

namespace KFTG
{

enum PlayerState
{
	STAND,
	WALK,
	JUMP,
	LIGHT_ATTACK,
	JUMP_LIGHT_ATTACK,
	HEAVY_ATTACK,
	JUMP_HEAVY_ATTACK,
	DEFEND
};

struct Player : public Component
{
	Player (Entity e, u16 i, u16 c, u16 h);

	Player& operator = (const Player &other);
	bool operator == (const Player &other);
	bool operator != (const Player &other);

	Entity owner;
	u16 id;
	u16 character;
	u16 health;
	PlayerState state;
	u16 stateTime;
	bool stateUpdated;
};

Player::Player (Entity e, u16 i, u16 c, u16 h)
	: Component (ComponentType::PLAYER), owner (e), id (i),
	character (c), health (h),
	state (PlayerState::STAND), stateTime (0)
{}

Player& Player::operator = (const Player &other)
{
	owner = other.owner;
	id = other.id;
	character = other.character;
	health = other.health;
	state = other.state;
	stateTime = other.stateTime;
	stateUpdated = other.stateUpdated;
	return *this;
}

bool Player::operator == (const Player &other)
{
	return id == other.id;
}

bool Player::operator != (const Player &other)
{
	return id != other.id;
}

}

#endif // PLAYER