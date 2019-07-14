#include "string.hpp"

namespace KFTG
{

string::string (const char *s)
	: len (0)
{
	while (s[len++])
		;
	str = (char*) Root::instance ()._memoryManager->allocAsset (len);
	std::memcpy (str, s, len);
}

string::string (const string &s)
	: len (s.len)
{
	str = (char*) Root::instance ()._memoryManager->allocAsset (len);
	std::memcpy (str, s.str, len);
}

string::~string ()
{
	Root::instance ()._memoryManager->freeAsset (str);
}

void string::insert (char c, u32 pos)
{
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (len + 1);
	std::memcpy (tmp, str, pos);
	tmp[pos] = c;
	std::memcpy (tmp, str + pos, len - pos);
	Root::instance ()._memoryManager->freeAsset (str);
	++len;
	str = tmp;
}

void string::erase (u32 pos, u32 l)
{
	if (pos + l >= len)
	{
		char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (pos);
		std::memcpy (tmp, str, pos);
		Root::instance ()._memoryManager->freeAsset (str);
		len = pos;
		str = tmp;
	}
	else
	{
		char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (len - l);
		std::memcpy (tmp, str, pos);
		std::memcpy (tmp + pos, str + pos + l, len - pos - l);
		Root::instance ()._memoryManager->freeAsset (str);
		len -= l;
		str = tmp;
	}
}

string& string::substr (u32 from, u32 l)
{
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (l);
	std::memcpy (tmp, str + from, l);
	string tmpstr (tmp);
	Root::instance ()._memoryManager->freeAsset (tmp);
	return tmpstr;
}

string& string::operator = (const string &s)
{
	Root::instance ()._memoryManager->freeAsset (str);
	len = s.len;
	str = (char*) Root::instance ()._memoryManager->allocAsset (len);
	std::memcpy (str, s.str, len);
	return *this;
}

string& string::operator += (const char c)
{
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (len + 1);
	std::memcpy (tmp, str, len);
	str[len++] = c;
	Root::instance ()._memoryManager->freeAsset (str);
	str = tmp;
	return *this;
}

string& string::operator += (const char *s)
{
	u32 l = 0;
	while (s[l++])
		;
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (len + l);
	std::memcpy (tmp, str, len);
	std::memcpy (tmp + len, s, l);
	len += l;
	Root::instance ()._memoryManager->freeAsset (str);
	str = tmp;
	return *this;
}

string& string::operator+= (const string &s)
{
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (len + s.len);
	std::memcpy (tmp, str, len);
	std::memcpy (tmp + len, s.str, s.len);
	len += s.len;
	Root::instance ()._memoryManager->freeAsset (str);
	str = tmp;
	return *this;
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

string& operator + (const char c, const string &s)
{
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (s.len + 1);
	tmp[0] = c;
	std::memcpy (tmp + 1, s.str, s.len);
	string tmps (tmp);
	Root::instance ()._memoryManager->freeAsset (tmp);
	return tmps;
}

string& operator + (const char *c, const string &s)
{
	u32 l = 0;
	while (c[l++])
		;
	char *tmp = (char*) Root::instance ()._memoryManager->allocAsset (s.len + l);
	std::memcpy (tmp, c, l);
	std::memcpy (tmp + l, s.str, s.len);
	string tmps (tmp);
	Root::instance ()._memoryManager->freeAsset (tmp);
	return tmps;
}

}