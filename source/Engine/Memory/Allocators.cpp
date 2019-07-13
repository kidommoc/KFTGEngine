#include "Allocators.hpp"

namespace KFTG
{

// HeapAllocator

HeapAllocator::HeapAllocator (u32 size)
	: _size (size), _freeBlock (nullptr),
	_pool (sizeof (BlockNode), MEM_STACK_POOL_LEN)
{
	_mem = new char[size];
	_freeBlock = (BlockNode*) _pool.alloc ();
	_freeBlock->p = _mem;
	_freeBlock->size = _size;
	_freeBlock->next = nullptr;
}

HeapAllocator::~HeapAllocator ()
{
	delete[] _mem;
}

void* HeapAllocator::alloc (u32 size)
{
	do
	{
		if (_freeBlock->size < size)
			continue;
		else if (_freeBlock->size == size)
		{
		}
		BlockNode *tmp = (BlockNode*) _pool.alloc ();
		tmp->p = _freeBlock->p + size;
		tmp->next = _freeBlock->next;
		tmp->size = _freeBlock->size - size;
		void *tmpreturn = _freeBlock->p;
		_freeBlock = tmp;
		return tmpreturn;
	} while (_freeBlock->next);
	
}

void HeapAllocator::free (void *p)
{
	BlockNode *tmp = _freeBlock;
}

// StackAllocator

StackAllocator::StackAllocator (u32 size)
	: _size (size), _markerL (0), _markerH (size)
{
	_mem = new char[size];
}

StackAllocator::~StackAllocator ()
{
	delete[] _mem;
}

void* StackAllocator::allocL (u32 size)
{
	if (size > _markerH - _markerL)
		return nullptr;
	void *tmp = _mem + _markerL;
	_markerL += size;
	return tmp;
}

void* StackAllocator::allocH (u32 size)
{
	if (size > _markerH - _markerL)
		return nullptr;
	void *tmp = _mem + _markerH - size;
	_markerH -= size;
	return tmp;
}

// Pool Allocator


PoolAllocator::PoolAllocator (u32 size, u32 len)
	: _mem (nullptr), _next (nullptr)
{
	if (size < 4)
		return;
	
	_mem = new char[size * len];
	_next = _mem;
	init (size, len);
}

PoolAllocator::~PoolAllocator ()
{
	delete[] _mem;
}

void* PoolAllocator::alloc ()
{
	void *tmp = _next;
	_next = *((void**) _next);
	return tmp;
}

void PoolAllocator::free (void *p)
{
	void **tmp = (void**) p;
	*tmp = *((void**) _next);
	_next = p;
}

void PoolAllocator::init (u32 size, u32 len)
{
	void **tmp = (void**) _next;
	for (u32 i = 0; i < len; ++i)
	{
		*tmp = *tmp + size;
		tmp = (void**) *tmp;
	}
}

}