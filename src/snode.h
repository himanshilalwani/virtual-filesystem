#ifndef SNODE_H
#define SNODE_H
#include<string>
using namespace std;

// Nodes of mylinkedlist which is a singly linked list used to implement a stack
class SNode
{
	private:
		string elem; // data
		SNode* next; // pointer to the next node
	public:
		SNode(string elem); // constructor
		friend class MyLinkedList;
};

#endif