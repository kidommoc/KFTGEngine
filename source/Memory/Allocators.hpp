#pragma once

#include "../Common/types.hpp"

#define MEM_STACK_POOL_LEN 4000

namespace KFTG
{

class PoolAllocator
{
public:
	PoolAllocator () = delete;
	explicit PoolAllocator (u32 size, u32 len);
	~PoolAllocator ();

	void *alloc ();
	void free (void *p);

private:
	void init (u32 size, u32 len);

	char *_mem;
	void *_next;
};

class HeapAllocator
{
public:
	HeapAllocator () = delete;
	explicit HeapAllocator (u32 size);
	~HeapAllocator ();

	void* alloc (u32 size);
	void free (void *p);

private:
	struct BlockNode
	{
		bool used;
		void *p;
		u32 size;
		BlockNode *prev;	
		BlockNode *next;
	};

	u32 _size;
	char *_mem;
	BlockNode *_blockNodes;
	PoolAllocator _pool;
};

class StackAllocator
{
public:
	StackAllocator (u32 size);
	~StackAllocator ();

	void* allocL (u32 size); // allocate from low end
	void* allocH (u32 size); // allocate from high end
	u32 getMarkerL () { return _markerL; }
	void freeLToMarker (u32 m) { _markerL = m; }
	u32 getMarkerH () { return _markerH; }
	void freeHToMarker (u32 m) { _markerH = m; }

private:
	u32 _size;
	char *_mem;
	u32 _markerL; // record stack top from low end
	u32 _markerH; // record stack "top" from high end
};

}