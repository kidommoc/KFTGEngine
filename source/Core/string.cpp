#include <cstring>
#include "string.hpp"
#include "Memory/MemoryManager.hpp"

namespace KFTG
{

string::string (const char *s)
	: len (0)
{
	while (s[len])
		len++;
	str = (char*) MemoryManager::instance ()->allocAsset (len);
	std::memcpy (str, s, len);
}

string::string (const string &s)
	: len (s.len)
{
	str = (char*) MemoryManager::instance ()->allocAsset (len);
	std::memcpy (str, s.str, len);
}

string::string (u32 num)
	: len (0)
{
	u32 tmp = 1;
	for (; num / tmp; tmp *= 10) 
		++len;
	str = (char*) MemoryManager::instance ()->allocAsset (len);
	tmp /= 10;
	for (int i = 0; i < len; ++i, tmp /= 10)
	{
		str[i] = num / tmp;
		num %= tmp;
	}
}

string::~string ()
{
	MemoryManager::instance ()->freeAsset (str);
}

void string::insert (char c, u32 pos)
{
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (len + 1);
	std::memcpy (tmp, str, pos);
	tmp[pos] = c;
	std::memcpy (tmp, str + pos, len - pos);
	MemoryManager::instance ()->freeAsset (str);
	++len;
	str = tmp;
}

void string::erase (u32 pos, u32 l)
{
	if (pos + l >= len)
	{
		char *tmp = (char*) MemoryManager::instance ()->allocAsset (pos);
		std::memcpy (tmp, str, pos);
		MemoryManager::instance ()->freeAsset (str);
		len = pos;
		str = tmp;
	}
	else
	{
		char *tmp = (char*) MemoryManager::instance ()->allocAsset (len - l);
		std::memcpy (tmp, str, pos);
		std::memcpy (tmp + pos, str + pos + l, len - pos - l);
		MemoryManager::instance ()->freeAsset (str);
		len -= l;
		str = tmp;
	}
}

string& string::substr (u32 from, u32 l)
{
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (l);
	std::memcpy (tmp, str + from, l);
	string tmpstr (tmp);
	MemoryManager::instance ()->freeAsset (tmp);
	return tmpstr;
}

string& string::operator = (const char *s)
{
	u32 l = 0;
	while (s[l])
		++l;
	MemoryManager::instance ()->freeAsset (str);
	len = l;
	str = (char*) MemoryManager::instance ()->allocAsset (len);
	std::memcpy (str, s, len);
	return *this;
}

string& string::operator = (const string &s)
{
	MemoryManager::instance ()->freeAsset (str);
	len = s.len;
	str = (char*) MemoryManager::instance ()->allocAsset (len);
	std::memcpy (str, s.str, len);
	return *this;
}

string& string::operator += (const char c)
{
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (len + 1);
	std::memcpy (tmp, str, len);
	str[len++] = c;
	MemoryManager::instance ()->freeAsset (str);
	str = tmp;
	return *this;
}

string& string::operator += (const char *s)
{
	u32 l = 0;
	while (s[l])
		l++;
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (len + l);
	std::memcpy (tmp, str, len);
	std::memcpy (tmp + len, s, l);
	len += l;
	MemoryManager::instance ()->freeAsset (str);
	str = tmp;
	return *this;
}

string& string::operator+= (const string &s)
{
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (len + s.len);
	std::memcpy (tmp, str, len);
	std::memcpy (tmp + len, s.str, s.len);
	len += s.len;
	MemoryManager::instance ()->freeAsset (str);
	str = tmp;
	return *this;
}

char& string::operator [] (u32 i)
{
	if (i >= 0 && i < len)
		return str[i];
	else
	{
		// TODO: error handling
		char c = 0;
		return c;
	}
}

char string::operator [] (u32 i) const
{
	if (i >= 0 && i < len)
		return str[i];
	else
		// TODO: error handling
		return 0;
}

string& string::operator + (const char c) const
{
	string tmp (*this);
	tmp += c;
	return tmp;
}

string& string::operator + (const char *s) const
{
	string tmp (*this);
	tmp += s;
	return tmp;
}

string& string::operator + (const string &s) const
{
	string tmp (*this);
	tmp += s;
	return tmp;
}

bool string::operator == (const string &s) const
{
	if (len != s.len)
		return false;
	for (u32 i = 0; i < len; ++i)
		if (str[i] != s.str[i])
			return false;
	return true;
}

bool string::operator == (const char *s) const
{
	u32 l = 0;
	while (s[l])
		++l;
	if (len != l)
		return false;
	for (u32 i = 0; i < len; ++i)
		if (str[i] != s[i])
			return false;
	return true;
}

bool string::operator != (const string &s) const
{
	return !(*this == s);
}

bool string::operator != (const char *s) const
{
	return !(*this == s);
}

string& operator + (const char c, const string &s)
{
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (s.len + 1);
	tmp[0] = c;
	std::memcpy (tmp + 1, s.str, s.len);
	string tmps (tmp);
	MemoryManager::instance ()->freeAsset (tmp);
	return tmps;
}

string& operator + (const char *c, const string &s)
{
	u32 l = 0;
	while (c[l])
		++l;
	char *tmp = (char*) MemoryManager::instance ()->allocAsset (s.len + l);
	std::memcpy (tmp, c, l);
	std::memcpy (tmp + l, s.str, s.len);
	string tmps (tmp);
	MemoryManager::instance ()->freeAsset (tmp);
	return tmps;
}

bool operator == (const char *s1, const string &s2)
{
	return s2 == s1;
}

bool operator != (const char *s1, const string &s2)
{
	return s2 != s1;
}

}