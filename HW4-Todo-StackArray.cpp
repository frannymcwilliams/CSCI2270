#include <iostream>
#include "HW4-Todo-StackArray.hpp"

using namespace std;

TodoStackArray::TodoStackArray()
{
	stackTop = -1;

	for(int i=0; i<MAX_STACK_SIZE; i++)
	{
		stack[i] = new TodoItem;
	}
}

bool TodoStackArray::isEmpty()
{
	if(stackTop == -1)
	{
		return true;
	}
	return false;
}

bool TodoStackArray::isFull()
{
	if(stackTop == MAX_STACK_SIZE-1)
	{
		return true;
	}
	return false;
}

void TodoStackArray::push(std::string todoItem)
{
	if(isFull())
	{
		cout << "Stack full, cannot add new todo item." << endl;
		return;
	}
	stackTop = stackTop+1;
	stack[stackTop] = new TodoItem;
	stack[stackTop]->todo = todoItem;
}

void TodoStackArray::pop()
{
	if(isEmpty())
	{
		cout << "Stack empty, cannot pop an item." << endl;
		return;
	}
	stackTop = stackTop-1;
}

TodoItem* TodoStackArray::peek()
{
	if(isEmpty())
	{
		cout << "Stack empty, cannot peek." << endl;
		TodoItem* empty = new TodoItem;
		empty = stack[stackTop];
		return empty;
	}
	TodoItem* temp = new TodoItem;
	temp = stack[stackTop];
	return temp;
}