#include "positionlist.h"
#include "node.h"
PositionList::PositionList() // constructor
{	
	//todo
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;	
}
//============================================================
PositionList::~PositionList() // destructor to clean up all nodes
{
	//todo
	while (!empty()) removeFront();
	delete head;
	delete tail;
}
//============================================================
bool PositionList::empty() const // is list empty?
{
	//todo
	return head->next == tail;
}
//============================================================
void PositionList::addBefore(Node *ptr, Position* p) // add position before ptr
{
	//todo
	Node* u = new Node;
	u->p = p;
	u->next = ptr;
	u->prev = ptr->prev;
	ptr->prev->next = u;
	ptr->prev = u;
}
//============================================================
void PositionList::addFront(Position* p) // add to front of list
{
	//todo
	Node* u = new Node;
	u->p = p;
	u->next = head->next;
	u->prev = head;
	head->next->prev = u;
	head->next = u; 
}
//============================================================
void PositionList::addBack(Position* p) // add to Back of the list
{
	//todo
	Node* u = new Node;
	u->p = p;
	u->next = tail;
	u->prev = tail->prev;
	tail->prev->next = u;
	tail->prev = u;
}
//============================================================
void PositionList::removeFront() // remove front item from list
{
	//todo
	if (head->next!=tail)
	{
		Node* old = head->next;
		head->next = old->next;
		old->next->prev = head;
		delete old; 
	} 
}
//============================================================
void PositionList::removeBack() // remove last item from list
{
	//todo
	if (tail->prev!=head)
	{
		Node* old = tail->prev;
		tail->prev = old->prev;
		old->prev->next = tail;
		delete old; 
	} 
}
//============================================================
void PositionList::remove(Position* p) // remove node with position p
{
	Node* v = head;
	while (v->next != NULL)
	{
		if (v->p == p)
		{
			Node* u = v->prev;
			Node* w = v->next;
			u->next = w;
			w->prev = u;
			delete v;
			break;
		}
		v = v->next;
	}	
}
//============================================================
PositionList::iterator::iterator(Node* u) // constructor
{
	this->v = u;
}
//============================================================
PositionList::iterator& PositionList::iterator::operator++() // moving to the next node using iterator
{
	if (v->next != NULL)
	{
		v = v->next;
		return *this;
	}
}
//============================================================
PositionList::iterator& PositionList::iterator::operator--() // moving to the previous node using iterator
{
	if (v->prev != NULL)
	{
		v = v->prev;
		return *this;	
	}		
}
//============================================================
Position* PositionList::iterator::operator*() // dereferencing the iterator 
{
	return v->p;
}
//============================================================
bool PositionList::iterator::operator==(const iterator& other) const // checking if two iterators are equal
{
	return v == other.v;
}
//============================================================
bool PositionList::iterator::operator!=(const iterator& other) const // checking if two iterators are unequal
{
	return v != other.v;
}
//============================================================
PositionList::iterator PositionList::begin() // iterator to the first node after head
{
return iterator(head->next);
}
//============================================================
PositionList::iterator PositionList::end() // iterator to tail
{
return iterator(tail);
}
//============================================================
// }