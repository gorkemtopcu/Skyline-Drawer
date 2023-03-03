#ifndef MODIFIEDPRIORITYQUEUE_H
#define MODIFIEDPRIORITYQUEUE_H

using namespace std;

class ModifiedPriorityQueue
{
private:

	struct Item
	{
		int value;
		int label;
		Item(int val = 0, int lab = -1):value(val), label(lab){}
	};
	int currentSize;
	int arrayCapacity;
	Item* heap;
	int* heapLocation;
	void percolateDown(int hole);

public:
	ModifiedPriorityQueue();
	ModifiedPriorityQueue(const int & capacity);
	~ModifiedPriorityQueue();
	
	void printHeap();
	void insert(const int & value, const int & label);
	int remove(const int & label);
	void makeEmpty();
	const int & getMax() const;
	bool isEmpty() const;
	bool isSingle() const;
};
#endif
