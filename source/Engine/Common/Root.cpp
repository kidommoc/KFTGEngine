#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
	_memoryManager = new MemoryManager ();
	_assetManager = new AssetManager ();
	//others
	_time = new Time ();

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

Root& Root::instance ()
{
	if (!_instance)
		_instance = new Root ();
	return *_instance;
}

void Root::loop ()
{
	_memoryManager->freeFrame ();
}

}