#include "ModifiedPriorityQueue.h"
#include <iostream>
using namespace std;

#pragma region Public Methods
ModifiedPriorityQueue::ModifiedPriorityQueue(const int & capacity = 10)
{
	heap = new Item[capacity + 2];
	heapLocation = new int[capacity + 2];
	arrayCapacity = capacity;
	currentSize = 0;
}

ModifiedPriorityQueue::~ModifiedPriorityQueue()
{
	delete [] heap;
	delete [] heapLocation;
};

void ModifiedPriorityQueue::insert(const int & value, const int & label)
{
	int hole = ++currentSize;

	for(;hole > 1 && value > heap[hole/2].value; hole/=2)
	{
		heap[hole] = heap[hole/2];
		heapLocation[heap[hole].label] = hole;
	}

	Item newItem = Item(value,label);

	heap[hole] = newItem;
	heapLocation[label] = hole;
}

int ModifiedPriorityQueue::remove(const int & label)
{
	if(isEmpty())
		return -1;

	heap[heapLocation[label]] = heap[currentSize--];

	percolateDown(heapLocation[label]);
	
	return heapLocation[label];
}

void ModifiedPriorityQueue::makeEmpty()
{
	for (int i = 1; i < arrayCapacity+1; i++)
	{
		cout << endl << endl;
		remove(i);
		printHeap();
	}
}

const int & ModifiedPriorityQueue::getMax() const
{
	return heap[1].value;
}

bool ModifiedPriorityQueue::isEmpty() const
{
	return currentSize == 0;
}

bool ModifiedPriorityQueue::isSingle() const
{
	return currentSize == 1;
}

void ModifiedPriorityQueue::printHeap()
{
	for (int i = 1; i < currentSize+1; i++)
	{
		cout << "value: " << heap[i].value << " - label: " << heap[i].label << " - heapLocation: " << heapLocation[heap[i].label] << endl;
	}
}
#pragma endregion

#pragma region Private Methods
void ModifiedPriorityQueue::percolateDown(int hole)
{
	int child;
	Item tmp = heap[hole];

	for(; hole*2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize && heap[child+1].value>heap[child].value)
			child++;
		if (heap[child].value>tmp.value)
		{
			heap[hole] = heap[child];
			heapLocation[heap[hole].label] = hole;
		}
		else
			break;
	}

	heap[hole] = tmp;
	heapLocation[tmp.label] = hole;
}
#pragma endregion
