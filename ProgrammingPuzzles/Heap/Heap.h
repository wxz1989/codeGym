#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef READ_DATA_FROM_FILE
//#define READ_DATA_FROM_FILE
#endif

#define INVALID -999999999
#define MAX_HEAP_SIZE 100


class Heap{
	static const int INT_CAPACITY = 10;
public:
	enum HeapType{
		MIN_HEAP = 0,
		MAX_HEAP,
	};

	Heap();
	Heap(HeapType heapType, size_t cap = INT_CAPACITY);
	~Heap();
private:
	//int heapArray[MAX_HEAP_SIZE];

	int* pHeapArray;
	HeapType mHeapType;
	size_t 	heapSize;
	size_t 	heapCapacity;
public:

	void Init(void);
	void Add(int value);
	bool Remove(int value);
	bool Update(int valueToUpdate, int newValue);

	void BuildHeap(int a[], int N);
		
	//int GetMin();
	//int GetMax();

	int Delete(void);
	int GetSize();

	//ToDo: Implement this and make it a complete expandable Heap Data Structure.
	void HeapSort(void);

	//This function checks Bounds of the child and parent indeices as well as their Values.
	// If values of parent and child violates current heapType then it will return false, otherwise validity is TRUE.
	bool IsValid(int childIndex  /*, int parent*/);
	int GetSwapIndex ( int left, int right, int parent);	
	void Clear(void);

	void SetHeapSize(size_t size);
	size_t GetHeapSize(void);

	void SetHeapCapacity(size_t cap);
	size_t GetHeapCapacity(void);

	void PrintHeap(void);
	std::string ToString(void);

	void SetHeapType(int type);
	int GetHeapType(void);
private:
	//Doubles size of the Heap data structure when Heap is alrady at it's max Capacity and a new element is inserted
	void Resize(void);
	void Heapify();
	void HeaptifyUtil(int index);
};