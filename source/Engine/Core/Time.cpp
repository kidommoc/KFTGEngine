#include <sys/time.h>
#include "Time.hpp"

namespace KFTG
{

Time* Time::instance ()
{
	static Time _instance;
	return &_instance;
}

void Time::init ()
{
	_currentTime = getTime ();
	_currentGameTime = 0;
	_prevFrameTime = _currentTime;
	_totalTime = 0;
	_isPause = false;
}

void Time::loop ()
{
	_prevFrameTime = _currentTime;
	_currentTime = getTime ();
	u32 tmp = _currentTime - _prevFrameTime;
	_totalTime += tmp;
	if (_isPause)
		_prevFrameTime = _currentTime;
	else
		_currentGameTime += tmp;
}

u64 Time::getTime ()
{
	struct timeval tp;
	gettimeofday (&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

}