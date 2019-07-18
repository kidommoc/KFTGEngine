#pragma once

#include <new>
#include "../Core/types.hpp"
#include "../Core/Module.hpp"
#include "../Core/Root.hpp"
#include "../Core/Math.hpp"
#include "../Memory/Allocators.hpp"
#include "AssetTypes.hpp"
#include "Filesystem.hpp"

#define ASSET_TABLE_SIZE 2000

namespace KFTG
{

class AssetRegistry
{
public:
	static AssetRegistry& instance ();
	~AssetRegistry ();

	void* queryAsset (const GUID &uid, u32 &size);
	void addAsset (const GUID &uid, void *asset, u32 size);
	void deleteAsset (GUID uid);
	void updateAssetAddr (void *former, void *later);

private:
	struct Element
	{
		Element () : guid (""), asset (nullptr) {}
		GUID guid;
		void *asset;
		u32 size;
	};

	AssetRegistry ();

	static AssetRegistry *_instance;
	u32 _tableUsed;
	Element *_table;
};

class AssetLoader
{
public:
	AssetLoader ();
	~AssetLoader ();
	// no need to divide data into multiple files temporarily
	// only all.data for all of serialized assets
	// and index.data for the data index in serialized xml
	void* loadAsset (const string &path);

private:
	AssetRegistry &_assetRegistry;
	Filesystem &_fs;
	XML *_index;
};

// May only be used by editor

class RawAssetLoader
{
public:
	RawAssetLoader ();
	~RawAssetLoader ();

private:
};

// May only be used by editor

class AssetPacker
{
public:
	AssetPacker ();
	~AssetPacker ();

private:
};

class AssetManager : public Module
{
public:
	AssetManager () {}
	~AssetManager () {}
	virtual void init ();
	virtual void exit ();
	void* queryAsset (const string &guid, u32 &size);

private:
	AssetLoader *_assetLoader;
	AssetRegistry *_assetRegistry;
};

}