#include "stack.h"
using namespace std;
#include<iostream>
#include<string>
// Exceptions
StackException::StackException(const string& err)
{
	this->errMsg = err;
}

string StackException::getError()
{
	return errMsg;
}
//=================================================
CStack::CStack():S(), n(0){}; // constructor
//=================================================
int CStack::size() const // size of the stack
{
	return n;
}
//=================================================

bool CStack::empty() const // checks if the stack is empty
{
	return n==0;
}
//=================================================
const string& CStack::top() const throw(StackException) // returns the reference of the element last added in the stack
{
	try
	{	
		return S.front();
		if (empty()) throw(StackException("Empty Stack"));		
	}
	catch (StackException& obj)
	{
		cout<<obj.getError();
	}
}
//=================================================
void CStack::push(const string& e) // inserts element at the end of the stack
{
	++n;
	S.addFront(e);
}
//=================================================
void CStack::pop() throw(StackException) // deletes element present at the end of the stack
{
	try 
	{
		if (empty()) throw(StackException("Empty Stack"));
		--n;
		S.removeFront();
	}
	catch (StackException& obj)
	{
		cout<<obj.getError();
	}
}