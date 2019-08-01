#pragma once

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
	QuitGame
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