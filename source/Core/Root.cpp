#include "Root.hpp"
#include <iostream>

namespace KFTG
{

Root::Root ()
{
	_memoryManager = MemoryManager::instance ();
	_assetManager = AssetManager::instance ();
	_eventManager = EventManager::instance ();
	//others
	_time = Time::instance ();

	_memoryManager->init ();
	_assetManager->init ();
	_eventManager->init ();
	//others
	_time->init ();

	_eventManager->registerEvent (Event::QuitGame, this);
}

Root::~Root ()
{
	_time->exit ();
	// others
	_assetManager->exit ();
	_eventManager->exit ();
	_memoryManager->exit ();
}

void Root::loop ()
{
	_memoryManager->freeFrame ();
	_time->loop ();
}

}