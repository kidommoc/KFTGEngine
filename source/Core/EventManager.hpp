#ifndef KFTG_EVENT_MANAGER
#define KFTG_EVENT_MANAGER

#include "../Common/types.hpp"
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"

#define EVENT_TYPE_NUM 15
#define EVENT_NUM 200

namespace KFTG
{

enum Event
{
	// TODO: more event
	QuitGame,
	KeyPress,
	KeyRelease
};

class EventListener
{
public:
	virtual void callback (void *param) = 0;
};

class QuitGameListener : public EventListener
{
public:
	virtual void callback (void *param) override;
	virtual void setQuit () = 0;
};

enum Keys
{
	TAB = 9,
	ESC = 27,
	SPACE = 32,
	ARROW_UP = 128,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,
	BACKSPACE,
	LEFT_CTRL,
	RIGHT_CTRL,
	LEFT_SHIFT,
	RIGHT_SHIFT,
	LEFT_ALT,
	RIGHT_ALT,
	CAPS_LOCK,
	F1, F2, F3, F4, F5, F6,
	F7, F8, F9, F10, F11, F12
};

class KeyPressListener : public EventListener
{
public:
	virtual void callback (void *param) override;
	virtual void whenKeyPress (u32 key) = 0;
};

class KeyReleaseListener : public EventListener
{
public:
	virtual void callback (void *param) override;
	virtual void whenKeyRelease (u32 key) = 0;
};

// TODO: more event listener

class EventManager : public Module, public Singleton
{
public:
	static EventManager* instance ();
	~EventManager () {}
	virtual void init () override;
	virtual void exit () override;

	void registerEvent (enum Event eventType, EventListener *listener);
	void unregisterEvent (enum Event eventType, EventListener *listener);
	void fireEvent (enum Event eventType, void *param);

private:
	EventManager () {}

	u32 _listenerCount[EVENT_TYPE_NUM];
	EventListener *_listeners[EVENT_TYPE_NUM][EVENT_NUM];
};

}

#endif // EVENT_MANAGER