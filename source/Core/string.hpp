#ifndef KFTG_STRING
#define KFTG_STRING

#include "../Common/types.hpp"

namespace KFTG
{

class string
{
public:
	string () : len (0), str (nullptr) {}
	string (const char *s);
	string (const string &s);
	string (u32 num);
	~string ();

	u32 getLen () const { return len; }
	const char* getCStr () const { return str; }
	void insert (char c, u32 pos);
	void insert (const string &s, u32 pos);
	void erase (u32 pos, u32 l);
	string& substr (u32 from, u32 l);

	string& operator = (const char *s);
	string& operator = (const string &s);
	string& operator += (const char c);
	string& operator += (const char *s);
	string& operator += (const string &s);
	char& operator [] (u32 i);
	char operator [] (u32 i) const;
	string& operator + (const char c) const;
	string& operator + (const char *s) const;
	string& operator + (const string &s) const;
	friend string& operator + (const char c, const string &s);
	friend string& operator + (const char *c, const string &s);
	bool operator == (const string &s) const;
	bool operator == (const char *s) const ;
	friend bool operator == (const char *s1, const string &s2);
	bool operator != (const string &s) const;
	bool operator != (const char *s) const;
	friend bool operator != (const char *s1, const string &s2);

private:
	u32 len;
	char *str;
};

string& operator + (const char c, const string &s);
string& operator + (const char *c, const string &s);
bool operator == (const char *s1, const string &s2);
bool operator != (const char *s1, const string &s2);

}

#endif // STRING