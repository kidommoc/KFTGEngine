#pragma once

namespace KFTG
{

template <class T>
class Singleton
{
public:
	static T* instance ()
	{
		return _instance;
	}

protected:
	static T *_instance;
};

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