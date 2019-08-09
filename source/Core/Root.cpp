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
	//_audioManager = AudioManager::instance ();
	//others
	_time = Time::instance ();
	_logic = Logic::instance ();

	_memoryManager->init ();
	_eventManager->init ();
	_assetManager->init ();
	_displayManager->init ();
	_inputManager->init ();
	//_audioManager->init ();
	_time->init ();
	_logic->init ();

	_eventManager->registerEvent (Event::Quit, this);
	_eventManager->registerEvent (Event::KeyPress,
		dynamic_cast<KeyPressListener*> (_inputManager));
	_eventManager->registerEvent (Event::KeyRelease,
		dynamic_cast<KeyPressListener*> (_inputManager));
}

Root::~Root ()
{
	_logic->exit ();
	_time->exit ();
	//_audioManager->exit ();
	_inputManager->exit ();
	_displayManager->exit ();
	_assetManager->exit ();
	_eventManager->exit ();
	_memoryManager->exit ();
}

void Root::loop ()
{
	_memoryManager->freeFrame ();
	_displayManager->loop ();
	//_audioManager->loop ();
	_time->loop ();
	_logic->loop ();
}

}