#pragma once

#include <windows.h>
#include "../Common/types.hpp"
#include "../Common/Math.hpp"

#define ASYNC_TABLE_SIZE 1000

namespace KFTG
{

class Filesystem
{
public:
	struct AsyncIOInfo
	{
		const string *path;
		void *buf;
		u32 size;
		Filesystem *fs;
		u32 index;
		void (*finish) (Filesystem *fs, u32 index);
	};

	static Filesystem& instance ();
	~Filesystem ();

	void touchFile (const string &path);
	u32 getFileSize (const string &path);
	void syncRead (const string &path, void *buf, u32 size);
	void syncWrite (const string &path, void *content, u32 size);
	void asyncRead (const string &path, void *buf, u32 size);
	void asyncWrite (const string &path, void *content, u32 size);
	bool queryAsyncIO (const string &path)
		{ return _tableAsync[hash (path) / 1000]; }
	void clearAsyncIO (const string &path)
		{ _tableAsync[hash (path) / 1000] = false; }
	friend void finishAsyncIO (Filesystem *fs, u32 index);
	friend void readThread (LPVOID lpParam);
	friend void writeThread (LPVOID lpParam);

private:
	Filesystem ();

	static Filesystem *_instance;
	bool *_tableAsync;
	PoolAllocator *_pool;
};

void finishAsyncIO (Filesystem *fs, u32 index);
void readThread (LPVOID lpParam);
void writeThread (LPVOID lpParam);

}