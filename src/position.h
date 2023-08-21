#ifndef POSITION_H
#define POSITION_H

#include<string>
#include "positionlist.h"
using namespace std;

class Position //inode w metadata
{
	private:
		string name; // name
		string date; // system date
		int size; // size
		Position* Parent; // pointer to the parent position
		PositionList Children; // list of children
		bool folder; // folder/file
	friend class Tree;
	friend class PositionList;
	friend class Node;

	public:
		Position(string name, string date, int size, bool type); // constructor
		Position* parent() const; // returns the pointer to the parent of current node
		PositionList children() const; // returns the list of children of current node
		bool isRoot() const; // checks if the current node is root
		bool isExternal() const; // checks if the current node is an external node
		void addChild(Position* c); // adds a position to Children
		void removeChild(Position* c); // removes the position from Children
};

#endif