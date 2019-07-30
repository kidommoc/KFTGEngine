#pragma once

namespace KFTG
{

class Module
{	
public:
	virtual void init () = 0;
	virtual void exit () = 0;
};

class LoopModule : public Module
{
public:
	virtual void loop () = 0;
};

}