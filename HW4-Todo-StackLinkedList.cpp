#include <iostream>
#include "HW4-Todo-StackLinkedList.hpp"

using namespace std;

TodoStackLinkedList::TodoStackLinkedList()
{
	stackHead = nullptr;
}

TodoStackLinkedList::~TodoStackLinkedList()
{
	while(!isEmpty())
	{
		pop();
	}
	stackHead = nullptr;
}

bool TodoStackLinkedList::isEmpty()
{
	if(stackHead != nullptr)
    {
    	return false;
    }
    return true;
}

void TodoStackLinkedList::push(std::string todoItem)
{
	//BASICALLY INSERTING AT THE BEGINNING OF A LINKED LIST

	//allocate a node
	TodoItem *newItem = new TodoItem;

	//Assign the value
	newItem->todo = todoItem;

	if(isEmpty())
	{
		stackHead = newItem;
		newItem->next = nullptr;
		return;
	}
	newItem->next = stackHead;
	stackHead = newItem;
	return;
}

void TodoStackLinkedList::pop()
{
	//BASICALLY DELTING FROM THE BEGINNIGN OF A LINKED LIST
	//create a temp node
	TodoItem* temp = new TodoItem;

	if(isEmpty())
	{
		cout << "Stack empty, cannot pop an item." << endl;
		return;
	}

	//assign head to temp
	temp = stackHead;

	//move head
	stackHead = stackHead->next;

	//delete temp
	delete temp;
	return;
}

TodoItem* TodoStackLinkedList::peek()
{
	//Returning the value at head
	if(isEmpty())
	{
		cout << "Stack empty, cannot peek." << endl;
		return nullptr;
	}
	return stackHead;
}