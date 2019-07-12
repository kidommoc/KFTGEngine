#pragma once

#include "../Common/types.hpp"
#include "../Common/Module.hpp"

#define MEM_STACK_SIZE 104857600

namespace KFTG
{

class StackAllocator
{
public:
	StackAllocator (u32 size);
	~StackAllocator ();
	void* allocL (u32 size);
	void* allocH (u32 size);
	u32 getMarkerL () { return _markerL; }
	void freeLToMarker (u32 m) { _markerL = m; }
	u32 getMarkerH () { return _markerH; }
	void freeHToMarker (u32 m) { _markerH = m; }

private:
	char *_mem;
	u32 _size;
	u32 _markerL;
	u32 _markerH;
};

class MemoryManager : public Module
{
public:
	MemoryManager () {}
	~MemoryManager () {}
	virtual void init ();
	virtual void exit ();

	void setScene ();
	void unsetScene ();
	void* allocGlobal (u32 size);
	void* allocScene (u32 size);
	void freeScene ();
	void* allocFrame (u32 size);
	void freeFrame ();

private:
	bool _inScene;
	StackAllocator *_allocator;
	u32 _allocatorSize;
	u32 _sceneMarker;
};

}