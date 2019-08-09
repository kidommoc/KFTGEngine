#include "System.hpp"

namespace KFTG
{

// System

void System::registerEntity (Entity e)
{
	for (auto entity : _entities)
		if (entity.id == e.id)
			return;
	_entities.append (e);
}

void System::unregisterEntity (Entity e)
{
	for (auto entity : _entities)
		if (entity.id == e.id)
		{
			entity = *(_entities.end () - 1);
			_entities.shrink ();
			return;
		}
}

}