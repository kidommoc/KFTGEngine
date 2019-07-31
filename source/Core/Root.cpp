#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
	_memoryManager = MemoryManager::instance ();
	_assetManager = AssetManager::instance ();
	//others
	_time = Time::instance ();

	_memoryManager->init ();
	_assetManager->init ();
	//others
	_time->init ();
}

Root::~Root ()
{
	_time->exit ();
	// others
	_assetManager->exit ();
	_memoryManager->exit ();
}

void Root::loop ()
{
	_memoryManager->freeFrame ();
	_time->loop ();
}

}