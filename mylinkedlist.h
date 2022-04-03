#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include<string>
#include "snode.h"
using namespace std;

class MyLinkedList
{
	private:
		SNode* head; // pointer to the head of list
	public:
		MyLinkedList (); // empty list constructor
		~MyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		void addFront(string elem); // add a new Node at the front of the list
		void removeFront(); // remove the node at the beginning
		const string& front() const; // return the element of the first node
};

#endif