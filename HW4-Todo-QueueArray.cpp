#include <iostream>
#include "HW4-Todo-QueueArray.hpp"

using namespace std;

TodoQueueArray::TodoQueueArray()
{
	queueFront = -1;
	queueEnd = -1;

	for(int i=0; i<MAX_QUEUE_SIZE; i++)
	{
		queue[i] = new TodoItem;
	}
}

bool TodoQueueArray::isEmpty()
{
	if(queueFront==-1 && queueEnd==-1)
	{
		return true;
	}
	return false;
}

bool TodoQueueArray::isFull()
{
	if((queueFront==0 && queueEnd==MAX_QUEUE_SIZE-1) || (queueFront==queueEnd+1))
	{
		return true;
	}
	return false;
}

void TodoQueueArray::enqueue(std::string todoItem)
{
	if(isFull())
	{
		cout << "Queue full, cannot add new todo item." << endl;
		return;
	}
	//if empty, add to index 0
	else if(isEmpty())
	{
		queueFront = 0;
		queueEnd = 0;
		queue[queueFront] = new TodoItem;
		queue[queueFront]->todo = todoItem;
	}
	//if the end of the queue is the end of the array, index is 0
	else if(queueEnd == MAX_QUEUE_SIZE-1)
	{
		queueEnd = 0;
		queue[queueEnd] = new TodoItem;
		queue[queueEnd]->todo = todoItem;
	}
	//add to next index in array
	else 
	{
		queueEnd = queueEnd+1;
		queue[queueEnd] = new TodoItem;
		queue[queueEnd]->todo = todoItem;
	}
}

void TodoQueueArray::dequeue()
{
	if(isEmpty())
	{
		cout << "Queue empty, cannot dequeue an item." << endl;
		return;
	}
	//only 1 thing in array so it is empty
	else if(queueFront == queueEnd)
	{
		queue[queueFront] = 0;
		queueFront = -1;
		queueEnd = -1;
	}
	//if front is at the end, it is now the beginning
	else if(queueFront == MAX_QUEUE_SIZE-1)
	{
		queue[queueFront] = 0;
		queueFront = 0;
	}
	//front is next index of array
	else
	{
		queue[queueFront] = 0;
		queueFront = queueFront+1;
	}
}

TodoItem* TodoQueueArray::peek()
{
	if(isEmpty())
	{
		cout << "Queue empty, cannot peek." << endl;
		TodoItem* empty = new TodoItem;
		empty = queue[queueFront];
		return empty;
	}
	TodoItem* temp = new TodoItem;
	temp = queue[queueFront];
	return temp;
}