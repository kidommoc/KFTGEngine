#ifndef KFTG_MAP
#define KFTG_MAP

#include "types.hpp"
#include "string.hpp"
#include "Math.hpp"
#include "Memory/MemoryManager.hpp"

#define MAP_CAPACITY 2000

namespace KFTG
{

template <typename T>
class map
{
public:
	map (bool isScene) : _isScene (isScene)
	{
		if (isScene)
			_table = (Element*) MemoryManager::instance ()
				->allocScene (MAP_CAPACITY * sizeof (Element));
		else
			_table = (Element*) MemoryManager::instance ()
				->allocAsset (MAP_CAPACITY * sizeof (Element));
	}

	~map ()
	{
		if (!_isScene)
			MemoryManager::instance ()->freeAsset (_table);
	}

	T* query (const string &k)
	{
		u32 h = hash (k) % MAP_CAPACITY;
		if (_table[h].key == k)
			return &_table[h].value;

		u16 i = 0;
		while (++i)
		{
			if (_table[(h + i * i) % MAP_CAPACITY].key == k)
				return &_table[(h + i * i) % MAP_CAPACITY].value;
			if (_table[(h - i * i) % MAP_CAPACITY].key == k)
				return &_table[(h - i * i) % MAP_CAPACITY].value;
		}
		return nullptr;
	}

	void add (const string &k, T t)
	{
		u32 h = hash (k) % MAP_CAPACITY;
		if (_table[h].key == "")
		{
			_table[h].key = k;
			_table[h].value = t;
			return;
		}

		u16 i = 0;
		while (++i)
		{
			if (_table[(h + i * i) % MAP_CAPACITY].key == "")
			{
				_table[(h + i * i) % MAP_CAPACITY].key = k;
				_table[(h + i * i) % MAP_CAPACITY].value = t;
				return;
			}
			if (_table[(h - i * i) % MAP_CAPACITY].key == "")
			{
				_table[(h - i * i) % MAP_CAPACITY].key = k;
				_table[(h - i * i) % MAP_CAPACITY].value = t;
				return;
			}
		}
	}

	void remove (const string &k)
	{
		u32 h = hash (k) % MAP_CAPACITY;
		if (_table[h].key == k)
		{
			_table[h].key = "";
			return;
		}

		u16 i = 0;
		while (++i)
		{
			if (_table[(h + i * i) % MAP_CAPACITY].key == k)
			{
				_table[(h + i * i) % MAP_CAPACITY].key = "";
				return;
			}
			if (_table[(h - i * i) % MAP_CAPACITY].key == k)
			{
				_table[(h - i * i) % MAP_CAPACITY].key = "";
				return;
			}
		}
	}

private:
	struct Element
	{
		string key;
		T value;
	};

	bool _isScene;
	Element *_table;
};

}

#endif // MAP