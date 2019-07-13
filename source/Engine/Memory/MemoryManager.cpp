#include "MemoryManager.hpp"

namespace KFTG
{

StackAllocator::StackAllocator (u32 size)
	: _size (size), _markerL (0), _markerH (size - 1)
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

void MemoryManager::init ()
{
	st = Status::Global;
	_allocatorSize = MEM_STACK_SIZE;
	_allocator = new StackAllocator (_allocatorSize);
}

void MemoryManager::exit ()
{
	delete _allocator;
}

void MemoryManager::setGlobal ()
{
	freeScene ();
	st = Status::Global;
}

void MemoryManager::setScene ()
{
	freeFrame ();
	_sceneMarker = _allocator->getMarkerL ();
}

void* MemoryManager::alloc (u32 size)
{
	void *tmp;
	switch (st)
	{
		case Status::Global:
		case Status::Scene:
			tmp = _allocator->allocL (size);
			break;
		case Status::Frame:
			tmp = _allocator->allocH (size);
			break;
		default:
			break;
	}
	return tmp;
}

void MemoryManager::freeScene ()
{
	if (st == Status::Scene)
		_allocator->freeLToMarker (_sceneMarker);
}

void MemoryManager::freeFrame ()
{
	if (st = Status::Frame)
		_allocator->freeHToMarker (_allocatorSize);
}

} //end namespace KFTG