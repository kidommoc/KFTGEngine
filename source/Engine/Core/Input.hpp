#pragma once

#include <windows.h>
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"

#define KEY_NUM 150

namespace KFTG
{

class InputManager : public LoopModule, public Singleton<InputManager>
{
public:
	enum Keys
	{
		ARROW_UP = 128,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		SHIFT,
		CTRL,
		ALT,
		BACKSPACE
	};

	InputManager () {}
	~InputManager () {}
	virtual void init ();
	virtual void exit ();
	virtual void loop ();

private:
	bool _inputBuf[KEY_NUM];
};

}