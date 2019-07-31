#include "InputManager.hpp"

namespace KFTG
{

InputManager* InputManager::instance ()
{
	static InputManager _instance;
	return &_instance;
}

void InputManager::init ()
{
}

void InputManager::exit ()
{
}

void InputManager::loop ()
{
}

}