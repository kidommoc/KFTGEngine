#include "MemoryManager.hpp"

namespace KFTG
{

// MemoryManager

void MemoryManager::init ()
{
	_stackAllocatorSize = MEM_STACK_SIZE;
	_stackAllocator = new StackAllocator (_stackAllocatorSize);
	_assetAllocatorSize = MEM_HEAP_SIZE;
	_assetAllocator = new HeapAllocator (_assetAllocatorSize);
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

PoolAllocator& MemoryManager::allocPool (u32 size, u32 len)
{
}

void MemoryManager::freeScene ()
{
	_stackAllocator->freeLToMarker (0);
}

void MemoryManager::freeFrame ()
{
	_stackAllocator->freeHToMarker (_stackAllocatorSize);
}

} //end namespace KFTG