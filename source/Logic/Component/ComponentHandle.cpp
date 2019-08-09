#include "ComponentHandle.hpp"

namespace KFTG
{

template <typename ComponentType>
void ComponentHandle<ComponentType>::destroy ()
{
	_world->removeComponent<ComponentType> (entity);
}

}