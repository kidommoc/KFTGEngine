#ifndef KFTG_INPUT_MANAGER
#define KFTG_INPUT_MANAGER

#include <windows.h>
#include "../Module.hpp"
#include "../Singleton.hpp"
#include "../Keys.hpp"
#include "EventManager.hpp"

#define KEY_NUM 150

namespace KFTG
{

class InputManager : public LoopModule, public Singleton,
	public KeyPressListener, public KeyReleaseListener
{
public:
	static InputManager* instance ();
	~InputManager () {}
	virtual void init ();
	virtual void exit ();
	virtual void loop ();

	virtual void whenKeyPress (u32 key) override;
	virtual void whenKeyRelease (u32 key) override;

	bool queryKeyPress (char key) const { return _pressBuf[key]; }
	bool queryKeyRelese (char key) const { return _releaseBuf[key]; }

private:
	InputManager () {}

	bool _pressBuf[KEY_NUM];
	bool _pressSyncBuf[KEY_NUM];
	bool _releaseBuf[KEY_NUM];
	bool _releaseSyncBuf[KEY_NUM];
};

}

#endif // INPUT_MANAGER