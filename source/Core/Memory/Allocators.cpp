#include "Allocators.hpp"

namespace KFTG
{

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
	// TODO: error handling
	void *tmp = _next;
	_next = *((void**) _next);
	return tmp;
}

void PoolAllocator::free (void *p)
{
	if (!p)
		return;
	void **tmp = (void**) p;
	*tmp = *((void**) _next);
	_next = p;
}

void PoolAllocator::init (u32 size, u32 len)
{
	void **tmp = (void**) _next;
	for (u32 i = 0; i < len; ++i)
	{
		*tmp = (void**) (((char*) tmp) + size);
		tmp = (void**) *tmp;
	}
}

// HeapAllocator

HeapAllocator::HeapAllocator (u32 size)
	: _size (size), _blockNodes (nullptr),
	_pool (sizeof (BlockNode), MEM_STACK_POOL_LEN)
{
	_mem = new char[size];
	_blockNodes = (BlockNode*) _pool.alloc ();
	_blockNodes->used = false;
	_blockNodes->p = _mem;
	_blockNodes->size = _size;
	_blockNodes->prev = nullptr;
	_blockNodes->next = nullptr;
}

HeapAllocator::~HeapAllocator ()
{
	delete[] _mem;
}

void* HeapAllocator::alloc (u32 size)
{
	if (size == 0)
		return nullptr; // TODO: error handling
	BlockNode *tmp = _blockNodes;
	while (tmp)
	{
		if (tmp->used || tmp->size < size)
		{
			tmp = tmp->next;
			continue;
		}

		if (tmp->size == size)
		{
			tmp->used = true;
			return tmp->p;
		}

		BlockNode *tmpnode = (BlockNode*) _pool.alloc ();
		tmpnode->used = false;
		tmpnode->p = tmp->p + size;
		tmpnode->next = tmp->next;
		tmpnode->size = tmp->size - size;
		tmp->size = size;
		tmp->next = tmpnode;
		tmp->used = true;
		_pool.free (tmp);
		return tmp->p;
	}
	return nullptr; // TODO: error handling
}

void HeapAllocator::free (void *p)
{
	BlockNode *tmp = _blockNodes;

	while (tmp)
	{
		if (tmp->p == p)
		{
			tmp->used = false;

			// Merge backward
			if (tmp->prev && !tmp->prev->used)
			{
				BlockNode *tmpb = tmp->prev;
				if (tmpb->prev)
					tmpb->prev->next = tmp;
				tmp->p = tmpb->p;
				tmp->size += tmpb->size;
				tmp->prev = tmpb->prev;
				_pool.free (tmpb);
			}

			// Merge forward
			if (tmp->next && !tmp->next->used)
			{
				BlockNode *tmpb = tmp->next;
				if (tmpb->next)
					tmpb->next->prev = tmp;
				tmp->p = tmpb->p;
				tmp->size += tmpb->size;
				tmp->next = tmpb->next;
				_pool.free (tmpb);
			}

			return;
		}
		tmp = tmp->next;
	}
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
	if (size == 0)
		return nullptr; // TODO: error handling
	if (size > _markerH - _markerL)
		return nullptr; // TODO: error handling
	void *tmp = _mem + _markerL;
	_markerL += size;
	return tmp;
}

void* StackAllocator::allocH (u32 size)
{
	if (size == 0)
		return nullptr; // TODO: error handling
	if (size > _markerH - _markerL)
		return nullptr; // TODO: error handling
	void *tmp = _mem + _markerH - size;
	_markerH -= size;
	return tmp;
}

}