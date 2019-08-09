#include "Logic.hpp"

namespace KFTG
{

Logic* Logic::instance ()
{
	static Logic _instance;
	return &_instance;
}

void Logic::init ()
{
}

void Logic::loop ()
{
}

void Logic::exit ()
{
}

}