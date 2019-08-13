#include "World.hpp"
#include <new>
#include "../../Core/Memory/MemoryManager.hpp"
#include "../../Core/Asset/AssetManager.hpp"
#include "../Component/Animator.hpp"
#include "../Component/Camera.hpp"
#include "../Component/Collider.hpp"
#include "../Component/HUD.hpp"
#include "../Component/Motion.hpp"
#include "../Component/Player.hpp"
#include "../Component/Sprite.hpp"
#include "../Component/Transform.hpp"

namespace KFTG
{

void World::init (GUID &sceneName)
{
	MemoryManager *memMgr = MemoryManager::instance ();
	AssetManager *assetMgr = AssetManager::instance ();
	_entityManager = new (memMgr->allocScene (sizeof (EntityManager)))
		EntityManager ();
	_uiManager = new (memMgr->allocScene (sizeof (EntityManager)))
		EntityManager ();

	initComponentMgrs ();

	XML *scene = (XML*) assetMgr->queryAsset (sceneName);

	typedef XML::Node::Attribute::Type AttrType;
	XML::Node::Attribute *sysMask = scene->root->findAttr ("systems");
	if (sysMask->type != AttrType::NUMBER)
		; // TODO: error handling
	initSystems (sysMask->value.n);

	initEntities (scene->root);

	EventManager::instance ()->registerEvent (Event::QuitScene, this);
}

void World::update (f32 deltaTime)
{
	for (auto sys : _systems)
		sys->update (deltaTime);
}

GUID* World::exit ()
{
	for (auto sys : _systems)
		sys->exit ();
	EventManager::instance ()->unregisterEvent (Event::QuitScene, this);
	MemoryManager::instance ()->freeScene ();
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

void World::initComponentMgrs ()
{
	MemoryManager *memMgr = MemoryManager::instance ();
	_componentManagers[ComponentType::PLAYER] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Player>)))
		ComponentManager<Player> ();
	_componentManagers[ComponentType::TRANSFORM] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Transform>)))
		ComponentManager<Transform> ();
	_componentManagers[ComponentType::MOTION] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Motion>)))
		ComponentManager<Motion> ();
	_componentManagers[ComponentType::CAMERA] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Camera>)))
		ComponentManager<Camera> ();
	_componentManagers[ComponentType::SPRITE] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Sprite>)))
		ComponentManager<Sprite> ();
	_componentManagers[ComponentType::ANIMATOR] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Animator>)))
		ComponentManager<Animator> ();
	_componentManagers[ComponentType::COLLIDER] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Collider>)))
		ComponentManager<Collider> ();
	_componentManagers[ComponentType::HUD] = 
		new (memMgr->allocScene (sizeof (ComponentManager<Hud>)))
		ComponentManager<Hud> ();
}

void World::initSystems (u32 mask)
{
	// ...
}

void World::initEntities (XML::Node *root)
{
	typedef XML::Node::Attribute::Type AttrType;
	for (XML::Node *e = root->firstChild; e; e = e->nextSibling)
	{
		EntityHandle *entity = createEntity ();
		for (XML::Node *c = e->firstChild; c; c = c->nextSibling)
		{
			XML::Node::Attribute *compType = e->findAttr ("ComponentType");
			if (compType->type != AttrType::NUMBER)
				continue; // TODO: error handling
			switch (compType->value.n)
			{
				// ...
				default:
					// TODO: error handling
					break;
			}
		}
	}
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