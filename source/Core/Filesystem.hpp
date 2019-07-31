#pragma once

#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"
#include "../Common/types.hpp"
#include "string.hpp"
#include "../Memory/Allocators.hpp"

#define ASYNC_TABLE_SIZE 1000

namespace KFTG
{

class Filesystem : public Singleton
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

	static Filesystem* instance ();
	~Filesystem ();

	void touchFile (const string &path);
	u32 getFileSize (const string &path);
	void syncRead (const string &path, void *buf, u32 size);
	void syncWrite (const string &path, void *content, u32 size);
	void asyncRead (const string &path, void *buf, u32 size);
	void asyncWrite (const string &path, void *content, u32 size);
	bool queryAsyncIO (const string &path);
	void clearAsyncIO (const string &path);
	friend void finishAsyncIO (Filesystem *fs, u32 index);
	friend void readThread (void *lpParam);
	friend void writeThread (void *lpParam);

private:
	Filesystem ();

	bool *_tableAsync;
	PoolAllocator *_pool;
};

void finishAsyncIO (Filesystem *fs, u32 index);
void readThread (void *lpParam);
void writeThread (void *lpParam);

}