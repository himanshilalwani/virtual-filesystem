#ifndef QUEUE_H
#define QUEUE_H

#include<string>
#include "position.h"

class Queue
{
	private:
		int f; //front element index
		int r; //index where a new element will be added
		int n; //size
		int N; //capacity
		Position* array[10];
		friend class Tree;

	public:
		Queue(); // constructor
		// Queue(int max); // constructor
		~Queue(); // destructor
		int size(); // returns the size of the queue
		bool empty(); // checks if the queue is empty
		Position* front(); // returns the element at the beginning of the queue
		void enqueue(Position* p); // adds a position at the next empty space
		void dequeue(); // deleted the position at the beginning of the queue
		void emptybin(); // empties the queue
};

#endif