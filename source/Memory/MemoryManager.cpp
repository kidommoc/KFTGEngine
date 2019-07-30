#include "MemoryManager.hpp"

namespace KFTG
{

// MemoryManager

MemoryManager* MemoryManager::instance ()
{
	static MemoryManager _instance;
	return &_instance;
}

void MemoryManager::init ()
{
	_stackAllocatorSize = MEM_STACK_SIZE;
	_stackAllocator = new StackAllocator (_stackAllocatorSize);
	_assetAllocatorSize = MEM_HEAP_SIZE;
	_assetAllocator = new HeapAllocator (_assetAllocatorSize);
	_XMLNodePool = new PoolAllocator (XML_NODE_SIZE, XML_NODE_POOL_LEN);
	_XMLAttrPool = new PoolAllocator (XML_ATTR_SIZE, XML_ATTR_POOL_LEN);
}

void MemoryManager::exit ()
{
	delete _stackAllocator;
	delete _assetAllocator;
}

void* MemoryManager::allocScene (u32 size)
{
	return _stackAllocator->allocL (size);
}

void* MemoryManager::allocFrame (u32 size)
{
	return _stackAllocator->allocH(size);
}

void* MemoryManager::allocAsset (u32 size)
{
	return _assetAllocator->alloc (size);
}

void MemoryManager::freeScene ()
{
	_stackAllocator->freeLToMarker (0);
}

void MemoryManager::freeFrame ()
{
	_stackAllocator->freeHToMarker (_stackAllocatorSize);
}

void MemoryManager::freeAsset (void *p)
{
	_assetAllocator->free (p);
}

} //end namespace KFTG