#pragma once

#include "types.hpp"
#include "../Memory/MemoryManager.hpp"
#include "Time.hpp"
#include "../Asset/AssetManager.hpp"

namespace KFTG
{

class Root
{
public:
	Root ();
	~Root ();

	void loop ();
	bool isQuit () { return _isQuit; }
	void setQuit () { _isQuit = true; }

private:
	bool _isQuit;

	//Modules
	MemoryManager *_memoryManager;
	Time *_time;
	AssetManager *_assetManager;
};

}