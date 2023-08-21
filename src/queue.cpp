#include "queue.h"
#include <iostream>
#include<exception>
using namespace std;

//=================================================
class QueueEmpty: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Queue is Empty"; 
		}
};
//=================================================
class QueueFull: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Queue is Full";
	}
};
//=================================================

Queue::Queue()
{
	this->f = 0;
	this->r = 0;
	this->n = 0;
	this->N = 10;
	// this->array = new Position*[N];
}

// Queue::Queue(int max)
// {
// 	this->f = 0;
// 	this->r = 0;
// 	this->n = 0;
// 	this->N = max;
// 	// this->array = new Position[N];
// }
//=================================================
Queue::~Queue() // constructor
{
	for (int i = 0; i < n; i++)
	{
		delete array[i];
	}
	
}
//=================================================
int Queue::size() // returns the size
{
	return n;
}
//=================================================
bool Queue::empty() // checks if the queue is empty
{
	return n==0;
}
//=================================================
Position* Queue::front() // returns the position at the front
{
	try
	{
		if (empty()) throw(QueueEmpty());
		return array[f];
	}
	catch(QueueEmpty &e)
	{
		e.what();
	}
}
//=================================================
void Queue::enqueue(Position* p) // inserts element at the next empty space
{
	try
	{
		if (size() == N) throw(QueueFull());
		array[r] = p;
		r = (r+1)%N;
		n = n + 1;
	}
	catch(QueueFull &e)
	{
		e.what();
	}
}
//=================================================
void Queue::dequeue() // deletes the position at the beginning
{
	try
	{
		if (empty()) throw(QueueEmpty());
		f = (f+1)%N;
		n = n - 1;
	}
	catch(QueueEmpty &e)
	{
		e.what();
	}
}
//=================================================
void Queue::emptybin() // empties the enitre bin
{
	if (empty())
	{
		cout<<"The bin is empty"<<endl;
	}
	while (!empty())
	{
		dequeue();
	}
}