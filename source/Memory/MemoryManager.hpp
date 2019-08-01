#pragma once

#include "../Common/types.hpp"
#include "../Common/Module.hpp"
#include "../Common/Singleton.hpp"
#include "Allocators.hpp"

#define MEM_STACK_SIZE 104857600
#define MEM_HEAP_SIZE 104857600
#define XML_NODE_SIZE 88
#define XML_NODE_POOL_LEN 3000
#define XML_ATTR_SIZE 40
#define XML_ATTR_POOL_LEN 12000

namespace KFTG
{

class MemoryManager : public Module, public Singleton
{
public:
	static MemoryManager* instance ();
	~MemoryManager () {}
	virtual void init () override;
	virtual void exit () override;

	void* allocScene (u32 size);
	void* allocFrame (u32 size);
	void* allocAsset (u32 size);
	void* allocXMLNode ();
	void* allocXMLAttr ();
	void freeScene ();
	void freeFrame ();
	void freeAsset (void *p);
	void freeXMLNode (void *p);
	void freeXMLAttr (void *p);

private:
	MemoryManager () {}

	StackAllocator *_stackAllocator;
	HeapAllocator *_assetAllocator;
	PoolAllocator *_XMLNodePool;
	PoolAllocator *_XMLAttrPool;
	u32 _stackAllocatorSize;
	u32 _assetAllocatorSize;
};

}