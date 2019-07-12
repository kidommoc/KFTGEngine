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
	_inScene = false;
	_allocatorSize = MEM_STACK_SIZE;
	_allocator = new StackAllocator (_allocatorSize);
}

void MemoryManager::exit ()
{
	delete _allocator;
}

void MemoryManager::setScene ()
{
	_inScene = true;
	_sceneMarker = _allocator->getMarkerL ();
}

void MemoryManager::unsetScene ()
{
	freeScene ();
	_inScene = false;
}

void* MemoryManager::allocGlobal (u32 size)
{
	if (!_inScene)
		return _allocator->allocL (size);
	else
		return nullptr;
	
}

void* MemoryManager::allocScene (u32 size)
{
	if (_inScene)
		return _allocator->allocL (size);
	else
		return nullptr;
}

void MemoryManager::freeScene ()
{
	if (_inScene)
		_allocator->freeLToMarker (_sceneMarker);
}

void* MemoryManager::allocFrame (u32 size)
{
	return _allocator->allocH (size);
}

void MemoryManager::freeFrame ()
{
	_allocator->freeHToMarker (_allocatorSize);
}

} //end namespace KFTG