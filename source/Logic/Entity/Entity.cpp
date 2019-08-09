#include "Entity.hpp"

namespace KFTG
{

void EntityHandle::destroy ()
{
	_world->destroyEntity (entity);
}

template <typename ComponentType>
void EntityHandle::addComponent (ComponentType &c)
{
	_world->addComponent<ComponentType> (_entity, c);
}

template <typename ComponentType>
void EntityHandle::removeComponent ()
{
	_world->removeComponent<ComponentType> (_entity);
}

}