#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
	_memoryManager = new MemoryManager ();
	_memoryManager->init ();
	// others
	_time = new Time ();
	_time->init ();
}

Root::~Root ()
{
	_time->exit ();
	// others
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