#ifndef KFTG_ARRAY
#define KFTG_ARRAY

#include "types.hpp"
#include "Memory/MemoryManager.hpp"
#include <cstring>

#define ARRAY_BLOCK_SIZE 50

namespace KFTG
{

// dynamic array (append only)

template <typename T>
class array
{
public:
	class iterator
	{
	public:
		iterator (u32 ind, array<T> *a) : index (ind), arr (a) {}
		T& operator * () { return a[index]; }
		iterator& operator + (u32 n) { index += n; }
		iterator& operator ++ () { ++index; }
		iterator& operator - (u32 n) { index -= n; }
		iterator& operator -- () { --index; }
	
	private:
		u32 index;
		array<T> *arr;
	};

	array ()
		: size (ARRAY_BLOCK_SIZE), capability (ARRAY_BLOCK_SIZE)
	{
		arr = (T*) MemoryManager::instance ()
			->allocAsset (ARRAY_BLOCK_SIZE * sizeof (T))
	}

	~array ()
	{
		MemoryManager::instance ()->freeAsset (arr);
	}

	u32 len () { return size; }
	iterator& begin () { return iterator (0, this); }
	iterator& end () { return iterator (size, this); }

	void append (T &e)
	{
		if (size >= capability)
		{
			T* tmp = (T*) MemoryManager::instance ()
				->allocAsset ((capability + ARRAY_BLOCK_SIZE) * sizeof (T))
			std::memcpy (tmp, arr, capability);
			MemoryManager::instance ()->freeAsset (arr);
			arr = tmp;
			capability += ARRAY_BLOCK_SIZE;
		}
		arr[size++] = e;
	}

	T& operator [] (u32 index) { return arr[index]; }
	const T& operator [] (u32 index) const { return arr[index]; }

private:
	u32 size;
	u32 capability;
	T *arr;
};

}

#endif // ARRAY