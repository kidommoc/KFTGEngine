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

template <class T> T* Singleton<T>::_instance = nullptr;

}