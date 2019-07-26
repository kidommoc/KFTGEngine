#pragma once

#include "string.hpp"
#include "../Common/types.hpp"

namespace KFTG
{

typedef string GUID;

struct Image
{
	struct Color
	{
		u8 red;
		u8 green;
		u8 blue;
		u8 alpha;
	};

	u16 width;
	u16 height;
	Color image[0];
};

struct Audio
{
};

class XML
{
public:
	struct Node
	{
		enum Type { NORMAL, VALUE };

		struct Attribute
		{
			string key;
			string value;
			Attribute *next;
		};

		void setType (enum Type t);
		// NORMAL
		Node* findChild (const string &childTag);
		void insertFirst (Node *n);
		void insertLast (Node *n);
		void insertBefore (Node *n, Node *before);
		void insertBefore (Node *n, const string &before);
		void insertAfter (Node *n, Node *after);
		void insertAfter (Node *n, const string &after);
		void removeChild (Node *n);
		void removeChild (const string &tag);

		Attribute* findAttr (const string &key);
		void appendAttr (Attribute *attr);
		void removeAttr (Attribute *attr);
		void removeAttr (const string &key);

		Node *parent;
		Node *firstChild;
		Node *lastChild;
		Node *prevSibling;
		Node *nextSibling;
		Attribute *attrs;
		enum Type type;
		string tag;
		string value;
	};

	Node* findNode (const string &tag);

private:
	Node *_root;
};

}