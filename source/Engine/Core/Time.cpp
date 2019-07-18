#include <sys/time.h>
#include "Time.hpp"

namespace KFTG
{

void Time::init ()
{
	_currentTime = getTime ();
	_currentGameTime = 0;
	_prevFrameTime = _currentTime;
	_totalTime = 0;
	_isPause = false;
	_instance = const_cast<Time*> (this);
}

void Time::loop ()
{
	if (_isPause)
		return;
	_prevFrameTime = _currentTime;
	_currentTime = getTime ();
	u32 tmp = _currentTime - _prevFrameTime;
	_currentGameTime += tmp;
	_totalTime += tmp;
}

u64 Time::getTime ()
{
	struct timeval tp;
	gettimeofday (&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

}