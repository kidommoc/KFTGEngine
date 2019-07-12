#include "Root.hpp"

namespace KFTG
{

Root::Root ()
{
}

Root::~Root ()
{
}

Root& Root::instance ()
{
	static Root _instance;
	return _instance;
}

void Root::loop ()
{
}

}