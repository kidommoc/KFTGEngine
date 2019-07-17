#pragma once

#include "types.hpp"
#include "../Memory/MemoryManager.hpp"
#include "Time.hpp"

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

private:
	Root ();
	bool _isQuit;
};

}