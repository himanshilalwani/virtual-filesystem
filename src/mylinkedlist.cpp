#include "mylinkedlist.h"
using namespace std;

MyLinkedList::MyLinkedList() // constructor
{
	head = NULL;
}
//=================================================
MyLinkedList::~MyLinkedList () // destructor
{
	while (!empty()) removeFront();
};
//=================================================
bool MyLinkedList::empty() const // checks if the list is empty
{
	return head == NULL;
};
//=================================================
void MyLinkedList::addFront(string elem) // adds a new node at the start of the list
{
	SNode* v = new SNode(elem);
	v->next = head;
	head = v;
};
//=================================================
void MyLinkedList::removeFront() // removes the node present at the beginning
{
	//todo
	SNode* old = head;
	head = old->next;
	delete old;
};
//=================================================
const string& MyLinkedList::front() const // returns a reference to the element present at the beginning of the list
{
	return head->elem;
}