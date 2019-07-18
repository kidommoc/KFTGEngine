#pragma once

#include "../Core/types.hpp"
#include "../Core/Module.hpp"
#include "Allocators.hpp"

#define MEM_STACK_SIZE 104857600
#define MEM_HEAP_SIZE 104857600

namespace KFTG
{

class MemoryManager : public Module, public Singleton<MemoryManager>
{
public:
	MemoryManager () {}
	~MemoryManager () {}
	virtual void init ();
	virtual void exit ();

	void* allocScene (u32 size);
	void* allocFrame (u32 size);
	void* allocAsset (u32 size);
	//PoolAllocator& allocPool (u32 size, u32 len);
	void freeScene ();
	void freeFrame ();
	void freeAsset (void *p);
	void freePool (PoolAllocator& p);

private:
	StackAllocator *_stackAllocator;
	HeapAllocator *_assetAllocator;
	u32 _stackAllocatorSize;
	u32 _assetAllocatorSize;
};

}