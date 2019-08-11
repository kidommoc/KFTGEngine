#include "Logic.hpp"
#include <new>
#include "../Core/Memory/MemoryManager.hpp"
#include "../Core/Asset/AssetManager.hpp"
#include "../Core/Time/Time.hpp"

namespace KFTG
{

Logic* Logic::instance ()
{
	static Logic _instance;
	return &_instance;
}

void Logic::init ()
{
	MemoryManager *memMgr = MemoryManager::instance ();
	AssetManager *assetMgr = AssetManager::instance ();
	_scene = (World*) memMgr->allocScene (sizeof (World));
#ifndef NODATA
	// TODO: create test data
	// ...
#endif
	u32 tmp;
	GUID *startScene = (GUID*) assetMgr->queryAsset ("StartScene");
	::new (_scene) World ();
	_scene->init (*startScene);
}

void Logic::loop ()
{
	_scene->update (Time::instance ()->getDeltaTime ());
	if (_scene->isQuit ())
	{
		// end this scene and get uid of next scene,
		GUID *nextScene = _scene->exit (); // (*)
		if (!nextScene)
		{
			EventManager::instance ()->fireEvent (Event::QuitGame, nullptr);
			return;
		}
		::new (_scene) World ();
		_scene->init (*nextScene);
	}
}

void Logic::exit ()
{
}

}