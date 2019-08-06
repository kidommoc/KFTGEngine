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
	for (u32 i = 0; i < KEY_NUM; ++i)
	{
		_pressBuf[i] = false;
		_pressSyncBuf[i] = false;
		_releaseBuf[i] = false;
		_releaseSyncBuf[i] = false;
	}
}

void InputManager::exit ()
{
}

void InputManager::loop ()
{
	for (u32 i = 0; i < KEY_NUM; ++i)
	{
		_pressBuf[i] = _pressSyncBuf[i];
		_releaseBuf[i] = _releaseSyncBuf[i];
		_releaseSyncBuf[i] = false;
	}
}

void InputManager::whenKeyPress (u32 key)
{
	_pressSyncBuf[key] = true;
}

void InputManager::whenKeyRelease (u32 key)
{
	_releaseSyncBuf[key] = true;
	_pressSyncBuf[key] = false;
}

}