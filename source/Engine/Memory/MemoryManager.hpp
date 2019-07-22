#pragma once

#include "../Core/types.hpp"
#include "../Core/Module.hpp"
#include "../Core/Singleton.hpp"
#include "Allocators.hpp"

#define MEM_STACK_SIZE 104857600
#define MEM_HEAP_SIZE 104857600
#define XML_NODE_SIZE 88
#define XML_NODE_POOL_LEN 3000
#define XML_ATTR_SIZE 40
#define XML_ATTR_POOL_LEN 12000

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
	PoolAllocator *_XMLNodePool;
	PoolAllocator *_XMLAttrPool;
	u32 _stackAllocatorSize;
	u32 _assetAllocatorSize;
};

}