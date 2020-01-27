#include <iostream>
#include "HW4-Todo-QueueLinkedList.hpp"

using namespace std;

TodoQueueLinkedList::TodoQueueLinkedList()
{
	queueFront = nullptr;
	queueEnd = nullptr;
}

TodoQueueLinkedList::~TodoQueueLinkedList()
{
	while(!isEmpty())
	{
		dequeue();
	}
	queueFront = nullptr;
	queueEnd = nullptr;
}

bool TodoQueueLinkedList::isEmpty()
{
	if(queueFront == nullptr || queueEnd == nullptr)
	{
		return true;
	}
    return false;
}

void TodoQueueLinkedList::enqueue(std::string todoItem)
{
	//BASICALLY INSERTING A NODE AT THE END
	//allocate a node
	TodoItem* newItem = new TodoItem;

	//assign the value
	newItem->todo = todoItem;
	newItem->next = nullptr;

	if(isEmpty())
	{
		queueFront = newItem;
	}
	else
	{
		queueEnd->next = newItem;
	}

	//moving the END to newItem
	queueEnd = newItem;
}

void TodoQueueLinkedList::dequeue()
{
	//point to front
	if(isEmpty())
	{
		cout << "Queue empty, cannot dequeue an item." << endl;
		return;
	}

	else
	{
		//create a temp pointer
		TodoItem* temp = new TodoItem;
		temp = queueFront;
		if(queueEnd == queueFront) //checking if queue contains only 1 element
		{
			queueFront = nullptr;
			queueEnd = nullptr;
		}
		else
		{
			//move the front to other next node
			queueFront = queueFront->next;
		}
		//delete temp
		delete temp;
	}
	return;
}

TodoItem* TodoQueueLinkedList::peek()
{
	if(isEmpty())
	{
		cout << "Queue empty, cannot peek." << endl;
		return nullptr;
	}
	return queueFront;
}