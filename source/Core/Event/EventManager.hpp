#ifndef KFTG_EVENT_MANAGER
#define KFTG_EVENT_MANAGER

#include "../types.hpp"
#include "../Module.hpp"
#include "../Singleton.hpp"
#include "../Keys.hpp"

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