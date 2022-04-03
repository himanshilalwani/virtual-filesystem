#ifndef STACK_H
#define STACK_H
#include <string>
#include "mylinkedlist.h"
using namespace std;


class StackException
{
	private:
		string errMsg;
	public:
		StackException(const string& err);
		string getError();
};

// template <typename T>
class CStack
{
	public:
		CStack();
		int size() const; // returns the size of the stack
		bool empty() const; // checks if the stack is empty
		const string& top() const throw(StackException); // returns the last element added in the stack
		void push(const string& e); // inserts element at the end of the stack
		void pop() throw(StackException); // removes the last element from the stack
	private:
		MyLinkedList S;
		int n;
};

#endif