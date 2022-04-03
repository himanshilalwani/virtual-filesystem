#ifndef POSITIONLIST_H
#define POSITIONLIST_H

#include <string>
// #include "position.h"
#include "node.h"
using namespace std;

// forward declarations
class Position;

class PositionList
{
	private:
		Node* head; // pointer ti the head of the list
		Node* tail; // pointer to the tail of List

		friend class Tree;
	public:
		PositionList();
		~PositionList();
		bool empty() const; // is list empty?
		void addBefore(Node *ptr, Position* p);	 //add a new position before ptr
		void addFront(Position* p); // add a new node to the front of list
		void addBack(Position* p); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void remove(Position *v);
		
		class iterator // iterator class
		{
			private:
				Node* v;

			public:
				friend class PositionList;
				friend class Tree;
				iterator(Node* u); // constructor
				// overloading the operators
				PositionList::iterator& operator++();
				PositionList::iterator& operator--();
				Position* operator*();
				bool operator==(const iterator& other) const;
				bool operator!=(const iterator& other) const;
		};

		PositionList::iterator begin(); // iterator of the front node
		PositionList::iterator end(); // iterator to the imaginary position at the end of the list
};

#endif