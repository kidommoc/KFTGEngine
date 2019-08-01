#pragma once

#include "../Common/types.hpp"
#include "../Memory/MemoryManager.hpp"
#include "Time.hpp"
#include "AssetManager.hpp"
#include "EventManager.hpp"
#include "DisplayManager.hpp"

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
	DisplayManager *_displayManager;
	Time *_time;
	AssetManager *_assetManager;
};

}