#include <new>
#include "AssetManager.hpp"
#include "../Math.hpp"
#include "../Memory/MemoryManager.hpp"

namespace KFTG
{

// AssetRegistry

AssetRegistry* AssetRegistry::instance ()
{
	static AssetRegistry _instance;
	return &_instance;
}

void* AssetRegistry::queryAsset (const GUID &uid, u32 &size)
{
	Element e = *_registry.query (uid);
	size = e.size;
	return e.asset;
}

void AssetRegistry::addAsset (const GUID &uid, void *asset, u32 size)
{
	Element e{asset, size};
	_registry.add (uid, e);
}

void AssetRegistry::deleteAsset (GUID uid)
{
	_registry.remove (uid);
}

// AssetLoader

AssetLoader::AssetLoader ()
	: _assetRegistry (AssetRegistry::instance ())
{
	_fs = Filesystem::instance ();
#ifndef NODATA
	u32 indexSize = _fs->getFileSize ("index.data");
	_index = (XML*) MemoryManager::instance ()->allocAsset (indexSize);
	_fs->syncRead ("index.data", _index, indexSize);
#endif
}

AssetLoader::~AssetLoader ()
{
	MemoryManager::instance ()->freeAsset (_index);
	delete _fs;
}

AssetLoader* AssetLoader::instance ()
{
	static AssetLoader _instance;
	return &_instance;
}

// TODO: load asset from data files

void* AssetLoader::loadAsset (const string &path)
{
	// will be finished after xml parser finished
	return nullptr;
}

// RawAssetLoader
// TODO: load asset from raw asset files

RawAssetLoader::RawAssetLoader ()
{
}

RawAssetLoader::~RawAssetLoader ()
{
}

// AssetPacker
// TODO: Pack cooked assets into data files

AssetPacker::AssetPacker ()
{
}

AssetPacker::~AssetPacker ()
{
}

// AssetManager

AssetManager* AssetManager::instance ()
{
	static AssetManager _instance;
	return &_instance;
}

void AssetManager::init ()
{
	_assetRegistry = AssetRegistry::instance ();
	_assetLoader = AssetLoader::instance ();
#ifndef NODATA
	_assetLoader->loadAsset ("all.data");
#endif
}

void AssetManager::exit ()
{
	delete _assetLoader;
	delete _assetRegistry;
}

void* AssetManager::queryAsset (const string &guid, u32 &size)
{
	return _assetRegistry->queryAsset (guid, size);
}

}