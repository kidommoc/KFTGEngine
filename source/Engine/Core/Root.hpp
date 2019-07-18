#pragma once

#include "types.hpp"
#include "engine.hpp"

namespace KFTG
{

class Root
{
public:
	~Root ();
	static Root& instance ();

	void loop ();
	bool isQuit () { return _isQuit; }
	void setQuit () { _isQuit = true; }

	//Modules
	MemoryManager *_memoryManager;
	Time *_time;
	AssetManager *_assetManager;

private:
	Root ();

	static Root *_instance;
	bool _isQuit;
};

}