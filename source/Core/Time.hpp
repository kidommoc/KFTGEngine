#pragma once

#include "../Common/types.hpp"
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"

namespace KFTG
{

class Time : public LoopModule, public Singleton
{
public:
	static Time* instance ();
	virtual void init ();
	virtual void exit () {}
	virtual void loop ();

	f32 getDeltaTime () const { return (_currentTime - _prevFrameTime) / 1000; }
	u32 getDeltaTimeMilli () const { return _currentTime - _prevFrameTime; }
	u64 getTotalTime () const { return _totalTime; }
	void pause () { _isPause = true; }
	void unpause () { _isPause = false; }

private:
	Time () {}
	u64 getTime ();

	u64 _currentTime;
	u64 _currentGameTime;
	u64 _prevFrameTime;
	u64 _totalTime;
	bool _isPause;
};

}