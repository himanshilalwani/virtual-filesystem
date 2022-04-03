#include "position.h"
//=================================================
Position::Position(string name, string date, int size, bool type) // constructor of the inode
{
	this->name = name;
	this->date = date;
	this->size = size;
	this->folder = type;
}
//=================================================
PositionList Position::children() const // returns the list of children
{
	return Children;
}
//=================================================
Position *Position::parent() const // returns the pointer to the parent of current position
{
	return Parent;
}
//=================================================
bool Position::isRoot() const // checks whether the current position is root
{
	return Parent == NULL;
};
//=================================================
bool Position::isExternal() const // checks whether the current position is an external node
{
	return Children.empty();
}
//=================================================
void Position::addChild(Position* c) // adds a position the list of children of current node
{
	Children.addBack(c);
}
//=================================================
void Position::removeChild(Position* c) // removes the position from the list of children of current node
{
	Children.remove(c);
}
//=================================================