#include "EntityManager.hpp"

namespace KFTG
{

Entity EntityManager::createEntity ()
{
	Entity e;
	e.id = _entityCount++;
	_entities.append (e);
	return e;
}

Entity EntityManager::createEntity (u16 pos)
{
	Entity e;
	e.id = _entityCount++;
	_entities.append (e);
	for (u16 i = pos + 1; i < _entities.len (); ++i)
		_entities[i] = _entities[i - 1];
	_entities[pos] = e;
	return e;
}

void EntityManager::destroyEntity (Entity e)
{
	for (u16 i = 0; i < _entities.len (); ++i)
		if (_entities[i] == e)
		{
			for (u16 j = i; j < _entities.len () - 1; ++j)
				_entities[j] = _entities[j + 1];
			_entities.shrink ();
			break;
		}
}


}