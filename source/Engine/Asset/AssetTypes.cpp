#include "AssetTypes.hpp"

namespace KFTG
{

void XML::Node::setType (enum Type t)
{
	if (t == Type::NORMAL)
	{
		type = t;
		// clear value
	}
	else if (t == Type::VALUE)
	{
		type = t;
		// clear children
	}
}

XML::Node* XML::Node::findChild (const string &childTag)
{
	if (type != Type::NORMAL)
		return nullptr;
	if (childTag == "")
		return nullptr;
	Node *tmp = firstChild;
	while (tmp)
	{
		if (tmp->tag == childTag)
			return tmp;
		tmp = tmp->nextSibling;
	}
	return nullptr;
}

void XML::Node::insertFirst (Node *n)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	firstChild->prevSibling = n;
	firstChild = n;
}

void XML::Node::insertLast (Node *n)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	lastChild->nextSibling = n;
	lastChild = n;
}

void XML::Node::insertBefore (Node *n, Node *before)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	if (before->prevSibling)
		before->prevSibling->nextSibling = n;
	else
		firstChild = n;
	n->parent = before->parent;
	n->nextSibling = before;
	n->prevSibling = before->prevSibling;
	before->prevSibling = n;
}

void XML::Node::insertBefore (Node *n, const string &before)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	insertBefore (n, findChild (before));
}

void XML::Node::insertAfter (Node *n, Node *after)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	if (after->nextSibling)
		after->nextSibling->prevSibling = n;
	else
		lastChild = n;
	n->parent = after->parent;
	n->prevSibling = after;
	n->nextSibling = after->nextSibling;
	after->nextSibling = n;
}

void XML::Node::insertAfter (Node *n, const string &after)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	insertAfter (n, findChild (after));
}

void XML::Node::removeChild (Node *n)
{
	if (type != Type::NORMAL)
		return;
	if (!n)
		return;
	if (n->prevSibling)
		n->prevSibling->nextSibling = n->nextSibling;
	else
		firstChild = n->nextSibling;
	if (n->nextSibling)
		n->nextSibling->prevSibling = n->prevSibling;
	else
		lastChild = n->prevSibling;
	// delete n
}

void XML::Node::removeChild (const string &tag)
{
	if (type != Type::NORMAL)
		return;
	if (tag == "")
		return;
	removeChild (findChild (tag));
}

XML::Node::Attribute* XML::Node::findAttr (const string &key)
{
	if (key == "")
		return nullptr;
	Attribute *tmp = attrs;
	while (tmp)
	{
		if (tmp->key == key)
			return tmp;
		tmp = tmp->next;
	}
	return nullptr;
}

void XML::Node::appendAttr (Attribute *attr)
{
	if (!attr)
		return;
	attr->next = attrs;
	attrs = attr;
}

void XML::Node::removeAttr (Attribute *attr)
{
	if (!attr)
		return;
	Attribute *tmp = attrs;
	while (tmp)
	{
		if (tmp->next == attr)
			break;
		tmp = tmp->next;
	}
	if (!tmp->next)
		return;
	tmp->next = attr->next;
	// delete attr;
}

void XML::Node::removeAttr (const string &key)
{
	if (key == "")
		return;
	removeAttr (findAttr (key));
}

}