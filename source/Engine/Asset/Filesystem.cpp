#include <windows.h>
#include "Filesystem.hpp"
#include "../Core/Math.hpp"

namespace KFTG
{

Filesystem& Filesystem::instance ()
{
	if (!_instance)
		_instance = new Filesystem ();
	return *_instance;
}

Filesystem::Filesystem ()
{
	_tableAsync = new bool[ASYNC_TABLE_SIZE];
	_pool = new PoolAllocator (sizeof (AsyncIOInfo), ASYNC_TABLE_SIZE);
}

Filesystem::~Filesystem ()
{
	delete[] _tableAsync;
	delete _pool;
}

void Filesystem::touchFile (const string &path)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle (hFile);
}

u32 Filesystem::getFileSize (const string &path)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	u32 size = GetFileSize (hFile, NULL);
	CloseHandle (hFile);
	return size;
}

void Filesystem::syncRead (const string &path, void *buf, u32 size)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	u32 bytesRead;
	ReadFile (hFile, buf, size, (LPDWORD) &bytesRead, NULL);
	CloseHandle (hFile);
}

void Filesystem::syncWrite (const string &path, void *content, u32 size)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_WRITE, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	u32 bytesWritten;
	WriteFile (hFile, content, size, (LPDWORD) &bytesWritten, NULL);
	CloseHandle (hFile);
}

void Filesystem::asyncRead (const string &path, void *buf, u32 size)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// Async Read
	AsyncIOInfo *info = (AsyncIOInfo*) _pool->alloc ();
	info->path = &path;
	info->buf = buf;
	info->size = size;
	info->fs = this;
	info->index = hash (path) / ASYNC_TABLE_SIZE;
	info->finish = finishAsyncIO;
	DWORD threadId;
	HANDLE hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) readThread,
		info, 0, &threadId);
	SetThreadPriority (hThread, THREAD_PRIORITY_BELOW_NORMAL);
}

void Filesystem::asyncWrite (const string &path, void *content, u32 size)
{
	HANDLE hFile = CreateFileA (path.getCStr (), GENERIC_WRITE, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// Async Write
}

bool Filesystem::queryAsyncIO (const string &path)
{
	return _tableAsync[hash (path) / 1000];
}

void Filesystem::clearAsyncIO (const string &path)
{
	_tableAsync[hash (path) / 1000] = false;
}

void finishAsyncIO (Filesystem *fs, u32 index)
{
	fs->_tableAsync[index] = true;
}

void readThread (LPVOID lpParam)
{
	Filesystem::AsyncIOInfo *info = (Filesystem::AsyncIOInfo*) lpParam;
	HANDLE hFile = CreateFileA (info->path->getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	u32 bytesRead;
	ReadFile (hFile, info->buf, info->size, (LPDWORD) &bytesRead, NULL);
	CloseHandle (hFile);
	info->finish (info->fs, info->index);
}

void writeThread (LPVOID lpParam)
{
	Filesystem::AsyncIOInfo *info = (Filesystem::AsyncIOInfo*) lpParam;
	HANDLE hFile = CreateFileA (info->path->getCStr (), GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	u32 bytesWritten;
	WriteFile (hFile, info->buf, info->size, (LPDWORD) &bytesWritten, NULL);
	CloseHandle (hFile);
	info->finish (info->fs, info->index);
}

}