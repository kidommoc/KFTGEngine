#include <new>
#include "AssetManager.hpp"
#include "../Core/Math.hpp"
#include "../Memory/Allocators.hpp"
#include "../Memory/MemoryManager.hpp"

namespace KFTG
{

// AssetRegistry

AssetRegistry::AssetRegistry ()
{
	_instance = const_cast <AssetRegistry*> (this);
}

AssetRegistry::~AssetRegistry ()
{
}

void* AssetRegistry::queryAsset (const GUID &uid, u32 &size)
{
	Element e = _registry.query (uid);
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
	_fs = new Filesystem ();
	u32 indexSize = _fs->getFileSize ("index.data");
	_index = (XML*) MemoryManager::instance ()->allocAsset (indexSize);
	_fs->syncRead ("index.data", _index, indexSize);
	_instance = const_cast<AssetLoader*> (this);
}

void* AssetLoader::loadAsset (const string &path)
{
	// will be finished after xml parser finished
}

AssetLoader::~AssetLoader ()
{
	MemoryManager::instance ()->freeAsset (_index);
	delete _fs;
}

// RawAssetLoader

RawAssetLoader::RawAssetLoader ()
{
}

RawAssetLoader::~RawAssetLoader ()
{
}

// AssetPacker

AssetPacker::AssetPacker ()
{
}

AssetPacker::~AssetPacker ()
{
}

// AssetManager

void AssetManager::init ()
{
	_assetRegistry = new AssetRegistry ();
	_assetLoader = new AssetLoader ();
	_assetLoader->loadAsset ("all.data");
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