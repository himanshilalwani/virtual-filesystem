#include "node.h"
#include <stddef.h>
//=================================================
Node::Node() // constructor
{
	next = NULL;
	prev = NULL; 
	p = NULL;
}
//=================================================
Node::Node(Position* p) // constructor
{
	this->p = p; 
	next = NULL; 
	prev = NULL;
}
//=================================================