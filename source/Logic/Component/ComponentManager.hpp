#ifndef KFTG_COMPONENT_MANAGER
#define KFTG_COMPONENT_MANAGER

#include "../../Core/types.hpp"
#include "../../Core/map.hpp"
#include "../../Core/array.hpp"
#include "../../Core/Event/EventManager.hpp"
#include "Component.hpp"
#include "../Entity/Entity.hpp"

namespace KFTG
{

class AbstractCM : public ComponentRemoveListener
{};

template <typename ComponentType>
class ComponentManager : public AbstractCM
{
public:
	ComponentManager ()
		: _componentsCount (0), _entityMap (true)
	{}

	~ComponentManager ();
	
	u16 add (Entity e, ComponentType &c)
	{
		u16 index = _componentsCount++;
		_entityMap.add (e.id, index);
		_components.append (c);
		_componentToEntity.append (e.id);
		return index;
	}

	void remove (Entity e)
	{
		--_componentsCount;
		u16 index = _entityMap.query (e.id);
		_entityMap.remove (e.id);
		_components[index] = _components[_componentsCount];
		_components.shrink ();
		_componentToEntity[index] = _componentToEntity[_componentsCount];
		_componentToEntity.shrink ();
	}

	void whenComponentRemove (u16 id) override
	{
		remove ({id});
	}

	ComponentType *queryComponent (Entity e)
	{
		return _components[_entityMap.query (e.id)];
	}

	Entity queryEntity (ComponentType &c)
	{
		for (u16 i = 0; i < _components.len (); ++i)
			if (_components[i] == c)
				return {_componentToEntity[i]};
	}

private:
	u16 _componentsCount;
	array<ComponentType> _components;
	array<u16> _componentToEntity;
	map<u16> _entityMap;
};

}

#endif // COMPONENT_MANAGER