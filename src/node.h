#ifndef NODE_H
#define NODE_H

// #include "position.h"
class Position;
using namespace std;

class Node // Node inside position list which is a doubly-linked list ADT of children
{
	private:
		Position* p; //data 
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		friend class PositionList;
		friend class Tree;
		
	public:
		Node();
		Node(Position* p);
};

#endif