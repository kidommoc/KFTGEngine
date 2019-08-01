#include "Root.hpp"
#include <iostream>

namespace KFTG
{

Root::Root ()
{
	_memoryManager = MemoryManager::instance ();
	_eventManager = EventManager::instance ();
	_assetManager = AssetManager::instance ();
	_displayManager = DisplayManager::instance ();
	//others
	_time = Time::instance ();

	_memoryManager->init ();
	_eventManager->init ();
	_assetManager->init ();
	_displayManager->init ();
	//others
	_time->init ();

	_eventManager->registerEvent (Event::QuitGame, this);
}

Root::~Root ()
{
	_time->exit ();
	// others
	_displayManager->exit ();
	_assetManager->exit ();
	_eventManager->exit ();
	_memoryManager->exit ();
}

void Root::loop ()
{
	_memoryManager->freeFrame ();
	_displayManager->loop ();
	_time->loop ();
}

}