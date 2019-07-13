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
	enum Status
	{
		Global, Scene, Frame
	};

	MemoryManager () {}
	~MemoryManager () {}
	virtual void init ();
	virtual void exit ();

	void setGlobal ();
	void setScene ();
	void setFrame ();
	void* alloc (u32 size);
	void freeScene ();
	void freeFrame ();

private:
	Status st;
	StackAllocator *_allocator;
	u32 _allocatorSize;
	u32 _sceneMarker;
};

}