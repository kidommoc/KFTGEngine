#include "World.hpp"
#include "../../Core/Event/EventManager.hpp"

namespace KFTG
{

void World::setQuit ()
{
	_isQuit = true;
}

EntityHandle* World::createEntity ()
{
	Entity e = _entityManager->createEntity ();
	_entityMasks.add (e.id, ComponentsMask ());
	EntityHandle handle (e, this);
	return &handle;
}

void World::destroyEntity (Entity e)
{
	for (auto sys : _systems)
		sys->unregisterEntity (e);
	EventManager::instance ()->fireEvent (Event::ComponentRemove, &e.id);
	_entityMasks.remove (e.id);
}

template <typename ComponentType>
void World::addComponent (Entity e, ComponentType &c)
{
	u16 type = ComponentType ().type;
	dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->add (e, c);
	ComponentsMask old = *_entityMasks.query (e.id);
	_entityMasks.query (e.id)->add (type);
	updateSystemCare (e, old);
}

template <typename ComponentType>
void World::removeComponent (Entity e)
{
	u16 type = ComponentType ().type;
	dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->remove (e);
	ComponentsMask old = *_entityMasks.query (e.id);
	_entityMasks.query (e.id)->remove (type);
	updateSystemCare (e, old);
}

template <typename ComponentType>
void World::getComponents (Entity e, ComponentType &c)
{
	u16 type = ComponentType ().type;
	c = dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->query (e);
}

template <typename ComponentType, typename... Args>
void World::getComponents (Entity e, ComponentType &c, Args &... args)
{
	u16 type = ComponentType ().type;
	c = dynamic_cast<ComponentManager<ComponentType>*> (_componentManagers[type])
		->query (e);

	getComponents (e, args ...);
}

void World::updateSystemCare (Entity e, ComponentsMask old)
{
	for (auto sys : _systems)
	{
		if (sys->getMask ().match (*_entityMasks.query (e.id)) &&
			!sys->getMask ().match (old))
			sys->registerEntity (e);
		if (sys->getMask ().match (old) &&
			!sys->getMask ().match (*_entityMasks.query (e.id)))
			sys->unregisterEntity (e);
	}
}

}