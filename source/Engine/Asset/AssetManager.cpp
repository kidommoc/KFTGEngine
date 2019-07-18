#include <new>
#include "AssetManager.hpp"
#include "../Core/Math.hpp"
#include "../Memory/Allocators.hpp"
#include "../Memory/MemoryManager.hpp"

namespace KFTG
{

// AssetRegistry

AssetRegistry::AssetRegistry ()
	: _tableUsed (0)
{
	_table = (Element*) MemoryManager::instance ()
		->allocAsset (ASSET_TABLE_SIZE * sizeof (Element));
	for (u32 i = 0; i < ASSET_TABLE_SIZE; ++i)
		::new (_table + i * sizeof (Element)) Element ();
	_instance = const_cast <AssetRegistry*> (this);
}

AssetRegistry::~AssetRegistry ()
{
	for (u32 i = 0; i < ASSET_TABLE_SIZE; ++i)
		if (_table[i].asset != nullptr)
			MemoryManager::instance ()->freeAsset (_table[i].asset);
	MemoryManager::instance ()->freeAsset (_table);
}

void* AssetRegistry::queryAsset (const GUID &uid, u32 &size)
{
	u32 h = hash (uid) % ASSET_TABLE_SIZE;
	if (_table[h].guid == uid)
	{
		size = _table[h].size;
		return _table[h].asset;
	}

	u16 i = 0;
	while (++i)
	{
		if (_table[(h + i * i) % ASSET_TABLE_SIZE].guid == uid)
		{
			size = _table[(h + i * i) % ASSET_TABLE_SIZE].size;
			return _table[(h + i * i) % ASSET_TABLE_SIZE].asset;
		}
		if (_table[(h - i * i) % ASSET_TABLE_SIZE].guid == uid)
		{
			size = _table[(h - i * i) % ASSET_TABLE_SIZE].size;
			return _table[(h - i * i) % ASSET_TABLE_SIZE].asset;
		}
	}
	size = 0;
	return nullptr;
}

void AssetRegistry::addAsset (const GUID &uid, void *asset, u32 size)
{
	if (_tableUsed >= ASSET_TABLE_SIZE)
		return;

	++_tableUsed;
	u32 h = hash (uid) % ASSET_TABLE_SIZE;
	if (_table[h].guid == "")
	{
		_table[h].guid = uid;
		_table[h].asset = asset;
		return;
	}

	u16 i = 0;
	while (++i)
	{
		if (_table[(h + i * i) % ASSET_TABLE_SIZE].guid == "")
		{
			_table[(h + i * i) % ASSET_TABLE_SIZE].guid = uid;
			_table[(h + i * i) % ASSET_TABLE_SIZE].asset = asset;
			_table[(h + i * i) % ASSET_TABLE_SIZE].size = size;
			return;
		}
		if (_table[(h - i * i) % ASSET_TABLE_SIZE].guid == "")
		{
			_table[(h - i * i) % ASSET_TABLE_SIZE].guid = uid;
			_table[(h - i * i) % ASSET_TABLE_SIZE].asset = asset;
			_table[(h - i * i) % ASSET_TABLE_SIZE].size = size;
			return;
		}
	}
}

void AssetRegistry::deleteAsset (GUID uid)
{
	u32 h = hash (uid) % ASSET_TABLE_SIZE;
	if (_table[h].guid == uid)
	{
		_table[h].guid = "";
		_table[h].asset = nullptr;
		return;
	}

	u16 i = 0;
	while (++i)
	{
		if (_table[(h + i * i) % ASSET_TABLE_SIZE].guid == uid)
		{
			_table[(h + i * i) % ASSET_TABLE_SIZE].guid = "";
			_table[(h + i * i) % ASSET_TABLE_SIZE].asset = nullptr;
			return;
		}
		if (_table[(h - i * i) % ASSET_TABLE_SIZE].guid == uid)
		{
			_table[(h - i * i) % ASSET_TABLE_SIZE].guid = "";
			_table[(h - i * i) % ASSET_TABLE_SIZE].asset = nullptr;
			return;
		}
	}
}

void AssetRegistry::updateAssetAddr (void *former, void *later)
{
	for (u32 i = 0; i < ASSET_TABLE_SIZE; ++i)
		if (_table[i].asset == former)
		{
			_table[i].asset = later;
			return;
		}
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