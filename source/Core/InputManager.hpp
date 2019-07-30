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
		BACKSPACE,
		HOME,
		PgUp,
		PgDn
	};

	InputManager () {}
	~InputManager () {}
	virtual void init ();
	virtual void exit ();
	virtual void loop ();

	bool queryKeyPress (char key) { return _pressBuf[key]; }
	bool queryKeyRelese (char key) { return _releaseBuf[key]; }

private:
	bool _pressBuf[KEY_NUM];
	bool _releaseBuf[KEY_NUM];
};

}