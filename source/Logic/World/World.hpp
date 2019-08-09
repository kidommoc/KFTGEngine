#ifndef KFTG_WORLD
#define KFTG_WORLD

#include "../../Core/array.hpp"
#include "../Entity/Entity.hpp"
#include "../Entity/EntityHandle.hpp"
#include "../Entity/EntityManager.hpp"
#include "../Component/Component.hpp"
#include "../Component/ComponentHandle.hpp"
#include "../Component/ComponentManager.hpp"
#include "../System/System.hpp"

namespace KFTG
{

class EntityHandle;
class AbstractCM;
class System;

// init (): instantiate entity manager, component managers and systems
//          and register events
// update (): call update()s of systems
// exit (): unregister events

class World : public QuitListener
{
public:
	void init (void *param);
	void update (f32 deltaTime);
	void exit ();

	void setQuit () override;

	EntityHandle* createEntity ();
	void destroyEntity (Entity e);

	template <typename ComponentType>
	void addComponent (Entity e, ComponentType &c);

	template <typename ComponentType>
	void removeComponent (Entity e);

	template <typename ComponentType>
	void getComponents (Entity e, ComponentType &c);

	template <typename ComponentType, typename... Args>
	void getComponents (Entity e, ComponentType &c, Args & ... args);

protected:
	void updateSystemCare (Entity e, ComponentsMask old);

	bool _isQuit;
	EntityManager *_entityManager;
	map<ComponentsMask> _entityMasks;
	AbstractCM *_componentManagers[COMPONENTS_NUM];
	array<System*> _systems;
};

}

#endif // WORLD