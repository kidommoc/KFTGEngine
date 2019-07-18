#include "AssetManager.hpp"

namespace KFTG
{

// AssetRegistry

AssetRegistry& AssetRegistry::instance ()
{
	if (!_instance)
		_instance = new AssetRegistry ();
	return *_instance;
}

AssetRegistry::AssetRegistry ()
	: _tableUsed (0)
{
	_table = (Element*) Root::instance ()._memoryManager
		->allocAsset (ASSET_TABLE_SIZE * sizeof (Element));
	for (u32 i = 0; i < ASSET_TABLE_SIZE; ++i)
		::new (_table + i * sizeof (Element)) Element ();
}

AssetRegistry::~AssetRegistry ()
{
	for (u32 i = 0; i < ASSET_TABLE_SIZE; ++i)
		if (_table[i].asset != nullptr)
			Root::instance ()._memoryManager->freeAsset (_table[i].asset);
	Root::instance ()._memoryManager->freeAsset (_table);
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
	: _assetRegistry (AssetRegistry::instance ()),
	_fs (Filesystem::instance ())
{
	u32 indexSize = _fs.getFileSize ("index.data");
	_index = (XML*) Root::instance ()._memoryManager->allocAsset (indexSize);
}

void* AssetLoader::loadAsset (const string &path)
{
	// will be finished after xml parser finished
}

AssetLoader::~AssetLoader ()
{
	Root::instance ()._memoryManager->freeAsset (_index);
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
	_assetLoader = new AssetLoader ();
	_assetRegistry = &AssetRegistry::instance ();
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