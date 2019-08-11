#ifndef KFTG_ASSET_TYPES
#define KFTG_ASSET_TYPES

#include "../types.hpp"
#include "../string.hpp"

namespace KFTG
{

typedef string GUID;

struct Image
{
	u16 width;
	u16 height;
	Color image[0];
};

struct Animation
{
	struct Clip
	{
		u16 time;
		Image *img;
	};

	u16 len;
	Clip ani[0];
};

struct Audio
{
	// TODO: audio struct
};

class XML
{
public:
	struct Node
	{
		enum Type { NORMAL, VALUE };

		struct Attribute
		{
			enum Type { STRING, NUMBER };

			Type type;
			string key;
			union Value
			{
				string s;
				u32 n;
			} value;
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
		void clearChild ();

		Attribute* findAttr (const string &key);
		void appendAttr (Attribute *attr);
		void removeAttr (Attribute *attr);
		void removeAttr (const string &key);

		enum Type type;
		string tag;
		Attribute *attrs;

		Node *parent;
		Node *firstChild;
		Node *lastChild;
		Node *prevSibling;
		Node *nextSibling;
		string value;
	};

	Node *root;
};

}

#endif // ASSET_TYPES