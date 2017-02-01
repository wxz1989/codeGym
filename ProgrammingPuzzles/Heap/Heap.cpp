#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef READ_DATA_FROM_FILE
#define READ_DATA_FROM_FILE
#endif

using namespace std;

#define INVALID -1
#define MAX_HEAP_SIZE 1000

void PrintHeapArray( int arrayp[], int size);

class Heap{

public:
	Heap();
	Heap(size_t size);

private:
	enum HeapType{
		MIN_HEAP = 0,
		MAX_HEAP,
	};
	int heapArray[MAX_HEAP_SIZE];

	HeapType type;
	size_t 	heapSize;
	int 	currentIndex;
public:
	void Add(int value);
	bool Remove(int value);
	bool Update(int valueToUpdate, int newValue);

	void BuildHeap(int a[], int N);
		
	int Min();
	int Max();
	int GetSize();

	void Clear(void);

	std::string ToString();

	void SetHeapType(int type);
	int GetHeapType(void);

private:
	void Heapify();
	void HeaptifyUtil(int index);
};


void Heap::Clear(void){
	memset(heapArray, 0, sizeof(int)* heapSize);
	currentIndex = 0;
	heapSize = 0;
}

void Heap::SetHeapType(int t){
	type = (HeapType)t;
}

int Heap::GetHeapType(void){
	return (HeapType)type;
}

Heap::Heap(){
	currentIndex = 0;
	type = (HeapType)0;
	heapSize = 0;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}
Heap::Heap(size_t t){
	type = (HeapType)t;
	currentIndex = 0;
	heapSize = 0;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}

void Heap::Add(int value){
	heapArray[currentIndex++] = value;
	Heapify();
	heapSize++;
}
bool Heap::Remove(int value){
	return false;
}
bool Heap::Update(int valueToUpdate, int newValue){
	return false;
}

void Heap::HeaptifyUtil(int parentIndex){
	int pivot = INVALID;

	int parent = heapArray[parentIndex];

	int lCIndex = 2 * parentIndex;
	int rCIndex = (2 * parentIndex) + 1;

	int lChild = heapArray[lCIndex];
	int rChild = heapArray[rCIndex];

	if (parentIndex < 1){ return; }

	// for min heap 
	if (type == MIN_HEAP){
		// MINHEAP RULE : Check if lChild index is LESS or EQUAL to heapSize
		//Also check for Min Heap Property
		// If current parent and leftChld relation violates Min Heap Property.
		// If it does than select the curent Parent as Pivot and swap Parent and Child values.

		if (lCIndex <= heapSize && lChild < parent ) { pivot = lCIndex; }
		if (rCIndex <= heapSize && rChild < parent ){ pivot = rCIndex; }
	} else {
		if (lCIndex <= heapSize && lChild > parent ){ pivot = lCIndex; }
		if (rCIndex <= heapSize && rChild > parent ){ pivot = rCIndex; }
	}

	if ( pivot != INVALID ){
		//Swap Smallest with parentIndex...
		int temp = heapArray[parentIndex];
		heapArray[parentIndex] = heapArray[pivot];
		heapArray[pivot] = temp;

		HeaptifyUtil(pivot);
		HeaptifyUtil(parentIndex);
	}
	return;
}

//Purpose of this function is to Copy value from the given HeapArray and use it for applying basic Heap algorithm HEAPIFY
void Heap::BuildHeap(int a[], int N){
	for (int i = 0; i< N; i++){ heapArray[i + 1] = a[i]; }
	heapSize = N;
	Heapify();
}

//Start from the middle of the heap and perform Heapify such that all element uptill root are covered
void Heap::Heapify(){
	for (int i = heapSize/2; i>0; i--){  HeaptifyUtil(i); }
}

//ToDo:Implement Min using Delete Root from MinHeap and Max using Delete Root in MaxHeap
int Heap::Min(){ return 0; }
int Heap::Max(){ return 0; }
int Heap::GetSize(){ return heapSize; }

std::string Heap::ToString(){
	std::string retValue;
	/*int index = 0;

	retValue.append("[");
	char buffer[100];
	for (index = 1; index < heapSize; index++){
	sprintf(buffer, "%d,", heapArray[index]);
	retValue.append(buffer);
	}
	sprintf(buffer, "%d]", heapArray[index]);
	retValue.append(buffer);*/
	
	std::cout << "Size:" << heapSize << std::endl;
	std::cout << "Heap:[";
	int i;
	for (i = 1; i < heapSize; i++){
		std::cout << heapArray[i] << ",";
	}
	std::cout << heapArray[i] << "]" <<  std::endl;
	return retValue;
}


int main(){

	Heap mHeap(0);

	int myArray[MAX_HEAP_SIZE] = { 0 };
	int test_cases = 0;
	int sizeOfHeap = 0;

#ifdef READ_DATA_FROM_FILE
	freopen("HeapSampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){
		
		cin >> sizeOfHeap;

		for (int i = 0; i < sizeOfHeap; i++){
			cin >> myArray[i];
		}

		cout <<"========================"<< endl;
		PrintHeapArray(myArray, sizeOfHeap);
		mHeap.BuildHeap(myArray, sizeOfHeap);
		mHeap.ToString();
		mHeap.Clear();
		//mHeap.GetHeapType() == 0 ? mHeap.SetHeapType(1) : mHeap.SetHeapType(0);
	}
#else
	srand(time(NULL));
	sizeOfHeap = rand()%20;
	srand(time(NULL));

	for ( int i = 0; i< sizeOfHeap;i++){
		int heapValue = rand()%99;
		myArray[i] = heapValue;	
	}

	cout <<"========================"<< endl;
	PrintHeapArray(myArray, sizeOfHeap);
	mHeap.BuildHeap(myArray, sizeOfHeap);
	mHeap.ToString();
	mHeap.Clear();

#endif
	return 0;
}

void PrintHeapArray( int array[], int size){
	int i;

	cout << "Org Heap Array:[";
	for ( i = 0; i<size-1;i++){ cout << array[i] << ","; }
	cout << array[i] << "]" << endl;
}