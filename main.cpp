#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ModifiedPriorityQueue.h"
using namespace std;

struct CoordinateData
{
	bool isLeft;
	int buildingID;
	int position;
	CoordinateData(bool left = true,int pos = 0 , int bID = -1):isLeft(left), position(pos), buildingID(bID){}
};

void shellSort(CoordinateData *& ptrArr, const int & capacity)
{
	int j;
	for (int gap = capacity; gap > 0; gap/=2)
		for(int i = gap; i < capacity; i++)
		{
			CoordinateData tmp = ptrArr[i];
			for (j = i; j  >= gap && tmp.position < ptrArr[j-gap].position; j -= gap)
				ptrArr[j] = ptrArr[j-gap];
			ptrArr[j] = tmp;
		}
}

void compareBuildings(int buildingCount, CoordinateData * coordArr, int * heightArray)
{
	ModifiedPriorityQueue mpq = ModifiedPriorityQueue(buildingCount+1);
	int currentMax = 0;
	for (int i = 0; i < buildingCount * 2; i++)
	{
		int currentPosition = coordArr[i].position;

		// check if the first iteration starts from position 0
		if(i == 0 && coordArr[0].position != 0)
			cout << "0 0" << endl;
		// do something with iterated element
		do
		{
			int currentLabel = coordArr[i].buildingID;
			// if element is a left coord insert it
			if(coordArr[i].isLeft)
			{
				mpq.insert(heightArray[currentLabel], currentLabel);
			}
			else // if right coord remove it
			{
				mpq.remove(currentLabel);
			}
			i++;
		}
		while(currentPosition == coordArr[i].position && i+1 < buildingCount * 2); // there might be duplicate values handle them in the same iteration
		i--;

		// display the current heights at current positions and update max height if necessary
		if(!mpq.isEmpty() && currentMax != mpq.getMax())
		{
			currentMax = mpq.getMax();
			cout << currentPosition << " " << currentMax << endl;
		}
		else if(mpq.isEmpty())
		{
			currentMax = 0;
			cout << currentPosition << " 0" << endl;
		}
	}
}

int main()
{
	string inputFileName = "input.txt";
	ifstream inputFile;
	inputFile.open(inputFileName.c_str());
	string line, capacityLine;
	int capacity, xLeft, xRight,coordIter = 0, y, labelID = 1;

	// get the capacity from first line
	getline(inputFile, capacityLine);
	capacity = stoi(capacityLine);
	CoordinateData * coordinateArray = new CoordinateData[(capacity * 2)];
	int * heightArray = new int[capacity+1];

	// get the x and y values from the remaining lines
	while(getline(inputFile, line))
	{
		istringstream ssLine(line);
		ssLine >> xLeft >> y >> xRight;

		// append x values to coordinate array
		coordinateArray[coordIter++] =  CoordinateData(true, xLeft, labelID);
		coordinateArray[coordIter++] = CoordinateData(false, xRight, labelID);

		// append y values to height array
		heightArray[labelID++] = y;
	}
	
	// sort recently constructed x-coordinate array
	shellSort(coordinateArray, capacity*2);

	compareBuildings(capacity, coordinateArray, heightArray);

	delete [] coordinateArray;
	return 0;
}

