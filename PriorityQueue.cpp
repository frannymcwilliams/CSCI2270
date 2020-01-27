#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "PriorityQueue.hpp"
using namespace std;

PriorityQueue::PriorityQueue(int _queueSize)
{
	maxQueueSize = _queueSize;
	priorityQueue = new PatientNode[maxQueueSize+1];
	currentQueueSize = 0;
}
PriorityQueue::~PriorityQueue()
{
	delete[] priorityQueue;
	priorityQueue = nullptr;
}
void PriorityQueue::enqueue (std::string _name, int _injurySeverity, int _treatmentTime)
{
	PatientNode tempPatient;
	tempPatient.name = _name;
	tempPatient.injurySeverity = _injurySeverity;
	tempPatient.treatmentTime = _treatmentTime;

	if(currentQueueSize == maxQueueSize)
	{
		return;
	}

	currentQueueSize++;
	priorityQueue[currentQueueSize] = tempPatient;
	repairUpward(currentQueueSize);
}
std::string PriorityQueue::peekName()
{
	if(currentQueueSize > 0)
	{
		return priorityQueue[1].name;
	}
	else
	{
		return "Empty";
	}
}
int PriorityQueue::peekInjurySeverity()
{
	if(currentQueueSize > 0)
	{
		return priorityQueue[1].injurySeverity;
	}
	else
	{
		return -1;
	}
}
int PriorityQueue::peekTreatmentTime()
{
	if(currentQueueSize > 0)
	{
		return priorityQueue[1].treatmentTime;
	}
	else
	{
		return -1;
	}
}
void PriorityQueue::dequeue()
{
	if(currentQueueSize <= 1)
	{
		currentQueueSize--;
	}
	else
	{
		priorityQueue[1] = priorityQueue[currentQueueSize];
		currentQueueSize--;
		repairDownward(1);
	}
}
bool PriorityQueue::isFull()
{
	if(currentQueueSize == maxQueueSize)
	{
		return true;
	}
	return false;
}
bool PriorityQueue::isEmpty()
{
	if(currentQueueSize == 0)
	{
		return true;
	}
	return false;
}

void swap(PatientNode *x, PatientNode *y)
{
    PatientNode temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueue::repairUpward(int nodeIndex)
{
	int index = nodeIndex/2;
	if(priorityQueue[index].injurySeverity < priorityQueue[nodeIndex].injurySeverity && index > 0)
	{
		swap(&priorityQueue[index], &priorityQueue[nodeIndex]);
		repairUpward(index);
	}
	else if(priorityQueue[index].injurySeverity == priorityQueue[nodeIndex].injurySeverity && index > 0)
	{
		if(priorityQueue[index].treatmentTime > priorityQueue[nodeIndex].treatmentTime)
		{
			swap(&priorityQueue[index], &priorityQueue[nodeIndex]);
			repairUpward(index);
		}
	}
}
void PriorityQueue::repairDownward(int nodeIndex)
{
	int left = 2*nodeIndex;
	int right = 2*nodeIndex+1;
	int index = nodeIndex;

	if(left <= currentQueueSize && (priorityQueue[left].injurySeverity > priorityQueue[index].injurySeverity 
		|| (priorityQueue[left].injurySeverity == priorityQueue[index].injurySeverity 
			&& priorityQueue[left].treatmentTime < priorityQueue[index].treatmentTime)))
	{
		index = left;
	}
	if(right <= currentQueueSize && (priorityQueue[right].injurySeverity > priorityQueue[index].injurySeverity 
		|| (priorityQueue[right].injurySeverity == priorityQueue[index].injurySeverity 
			&& priorityQueue[right].treatmentTime < priorityQueue[index].treatmentTime))) 
	{
		index = right;
	}

	if(index != nodeIndex)
	{
		swap(&priorityQueue[index], &priorityQueue[nodeIndex]);
		repairDownward(index);
	}	
}




