#ifndef KFTG_ROOT
#define KFTG_ROOT

#include "types.hpp"
#include "Memory/MemoryManager.hpp"
#include "Event/EventManager.hpp"
#include "Asset/AssetManager.hpp"
#include "Display/DisplayManager.hpp"
#include "Event/InputManager.hpp"
#include "Time/Time.hpp"
#include "Audio/AudioManager.hpp"

namespace KFTG
{

class Root : public QuitGameListener
{
public:
	Root ();
	~Root ();

	void loop ();
	bool isQuit () { return _isQuit; }
	virtual void setQuit () override { _isQuit = true; }

private:
	bool _isQuit;

	//Modules
	MemoryManager *_memoryManager;
	EventManager *_eventManager;
	AssetManager *_assetManager;
	DisplayManager *_displayManager;
	InputManager *_inputManager;
	AudioManager *_audioManager;
	Time *_time;
};

}

#endif // ROOT