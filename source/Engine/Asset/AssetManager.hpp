#pragma once

#include "../Core/string.hpp"
#include "../Core/types.hpp"
#include "../Core/Module.hpp"
#include "../Core/map.hpp"
#include "AssetTypes.hpp"
#include "Filesystem.hpp"

#define ASSET_TABLE_SIZE 2000

namespace KFTG
{

class AssetRegistry : public Singleton<AssetRegistry>
{
public:
	AssetRegistry ();
	~AssetRegistry ();

	void* queryAsset (const GUID &uid, u32 &size);
	void addAsset (const GUID &uid, void *asset, u32 size);
	void deleteAsset (GUID uid);

private:
	struct Element
	{
		Element () : asset (nullptr), size (0) {}
		Element (void *a, u32 s) : asset (a), size (s) {}
		Element (const Element &e) : asset (e.asset), size (e.size) {}
		void *asset;
		u32 size;

		const Element& operator = (const Element &e)
			{ asset = e.asset; size = e.size; }
	};

	map<Element> _registry;
};

class AssetLoader : public Singleton<AssetLoader>
{
public:
	AssetLoader ();
	~AssetLoader ();
	// no need to divide data into multiple files temporarily
	// only all.data for all of serialized assets
	// and index.data for the data index in serialized xml
	void* loadAsset (const string &path);

private:
	AssetRegistry *_assetRegistry;
	Filesystem *_fs;
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