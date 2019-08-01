#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
	_memoryManager = MemoryManager::instance ();
	_eventManager = EventManager::instance ();
	_assetManager = AssetManager::instance ();
	_displayManager = DisplayManager::instance ();
	_inputManager = InputManager::instance ();
	//others
	_time = Time::instance ();

	_memoryManager->init ();
	_eventManager->init ();
	_assetManager->init ();
	_displayManager->init ();
	_inputManager->init ();
	//others
	_time->init ();

	_eventManager->registerEvent (Event::QuitGame, this);
	_eventManager->registerEvent (Event::KeyPress,
		dynamic_cast<KeyPressListener*> (_inputManager));
	_eventManager->registerEvent (Event::KeyRelease,
		dynamic_cast<KeyPressListener*> (_inputManager));
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