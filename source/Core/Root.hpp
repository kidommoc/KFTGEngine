#pragma once

#include "../Common/types.hpp"
#include "../Memory/MemoryManager.hpp"
#include "EventManager.hpp"
#include "AssetManager.hpp"
#include "DisplayManager.hpp"
#include "InputManager.hpp"
#include "Time.hpp"
#include "AudioManager.hpp"

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