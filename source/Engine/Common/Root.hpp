#pragma once

#include "types.hpp"

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

private:
	Root ();
	bool _isQuit;
};

}