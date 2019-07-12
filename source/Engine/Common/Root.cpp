#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
	_memoryManager.init ();
}

Root::~Root ()
{
	_memoryManager.exit ();
}

Root& Root::instance ()
{
	static Root _instance;
	return _instance;
}

void Root::loop ()
{
	_memoryManager.freeFrame ();
}

}