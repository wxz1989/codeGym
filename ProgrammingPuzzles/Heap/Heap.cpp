#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef READ_DATA_FROM_FILE
//#define READ_DATA_FROM_FILE
#endif

using namespace std;

#define INVALID -1
#define MAX_HEAP_SIZE 1000

void PrintHeapArray( int arrayp[], int size);
void ResetHeapArray(int myArray[],int sizeOfHeap);

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
public:
	void Add(int value);
	bool Remove(int value);
	bool Update(int valueToUpdate, int newValue);

	void BuildHeap(int a[], int N);
		
	int GetMin();
	int GetMax();
	int GetSize();

	void Clear(void);

	void SetHeapSize(size_t size);
	size_t GetHeapSize(void);

	std::string ToString();

	void SetHeapType(int type);
	int GetHeapType(void);

private:
	void Heapify();
	void HeaptifyUtil(int index);
};


void Heap::SetHeapSize(size_t size){
	heapSize = size;
}

size_t Heap::GetHeapSize(void){
	return heapSize;
}

void Heap::Clear(void){
	memset(heapArray, 0, sizeof(int)* heapSize);
	heapSize = 0;
	SetHeapSize(0);
}

void Heap::SetHeapType(int t){
	type = (HeapType)t;
}

int Heap::GetHeapType(void){
	return (HeapType)type;
}

Heap::Heap(){
	type = (HeapType)0;
	heapSize = 0;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}
Heap::Heap(size_t t){
	type = (HeapType)t;
	heapSize = 0;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}

void Heap::Add(int value){
	heapArray[(heapSize++)+1] = value;
	if ( heapSize > 1 ){  Heapify(); }	
}
bool Heap::Remove(int value){
	return false;
}
bool Heap::Update(int valueToUpdate, int newValue){
	return false;
}

//ToDo:Implement Min using Delete Root from MinHeap and Max using Delete Root in MaxHeap
int Heap::GetMin(){ 

	if ( heapSize == 0 ) { cout << "Error: Empty Heap" << endl; return -1;}
	if ( type != MIN_HEAP){ cout << "Invalid request, this is MIN HEAP" << endl; return -1; }

	int minValue = heapArray[1];
	for( int i = 1; i<heapSize+1; i++){ heapArray[i] = heapArray[i+1]; }
	heapSize--;

	Heapify();

	return minValue; 
}
int Heap::GetMax(){ 
	if ( heapSize == 0 ) { cout << "Error :Empty Heap" << endl; return -1;}
	if ( type != MAX_HEAP){ cout << "Error: Invalid request, this is MAX HEAP" << endl; return -1; }

	int minValue = heapArray[1];
	for( int i = 1; i<heapSize; i++){ heapArray[i] = heapArray[i+1]; }
	heapSize--;

	Heapify();

	return minValue; 
}
int Heap::GetSize(){ return heapSize; }

//Purpose of this function is to Copy value from the given HeapArray and use it for applying basic Heap algorithm HEAPIFY
void Heap::BuildHeap(int a[], int N){
	for (int i = 0; i< N; i++){ heapArray[i + 1] = a[i]; }
	heapSize = N;
	Heapify();
}

//Start from the middle of the heap and perform Heapify such that all element uptill root are covered
void Heap::Heapify(){
	bool bSwap = false;

	if ( heapSize <= 1 ){ return; }

	//ToDo: Improve on code qiality and algorithm here, shouldn't have to deal using two cases.
	// Case for heap with more than 2 elements
	if( heapSize > 2 ){
		for (int i = heapSize/2; i>0; i--){ HeaptifyUtil(i); }	
	} else {   	// Case for heap with more than <=2 elements
		//as thre are only 2 elements compare the elements for Min/Max and Swap if required
		if (type == MIN_HEAP){ 
			if ( heapArray[1] > heapArray[2] ) {  bSwap = true; }
		} else {
			if ( heapArray[1] < heapArray[2] ) {  bSwap = true; }
		}
		if ( bSwap ){
			int temp = heapArray[1];
			heapArray[1] = heapArray[2];
			heapArray[2] = temp;
		}
	}
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

std::string Heap::ToString(){
	std::string retValue("");
	
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

		mHeap.SetHeapSize(sizeOfHeap);

		for (int i = 0; i < mHeap.GetHeapSize(); i++){
			cin >> myArray[i];
			mHeap.Add(myArray[i]);
		}

		cout <<"========================"<< endl;
		PrintHeapArray(myArray, mHeap.GetHeapSize());
		//mHeap.BuildHeap(myArray, sizeOfHeap);
		mHeap.ToString();
		mHeap.Clear();
		ResetHeapArray(myArray, mHeap.GetHeapSize());
		//mHeap.GetHeapType() == 0 ? mHeap.SetHeapType(1) : mHeap.SetHeapType(0);
	}
#else
	srand(time(NULL));
	sizeOfHeap = rand()%10;
	srand(time(NULL));

	//mHeap.SetHeapSize(sizeOfHeap);

	for ( int i = 0; i< sizeOfHeap;i++){
		int heapValue = rand()%20;
		myArray[i] = heapValue;	
		mHeap.Add(myArray[i]);
	}

	cout <<"========================"<< endl;
	PrintHeapArray(myArray, mHeap.GetHeapSize());
	//mHeap.BuildHeap(myArray, sizeOfHeap);
	mHeap.ToString();
	//mHeap.Clear();
	//ResetHeapArray(myArray, sizeOfHeap);

	while ( mHeap.GetSize() > 0 ){
		int min = -1;
		min = mHeap.GetMin();
		if( min != -1 ){
			cout << "Min: " << min << endl;
		} else {
			cout << "Invalid min" << endl;
		}
		//mHeap.ToString();
	}


#endif
	return 0;
}

void ResetHeapArray(int array[], int size){
	for ( int i = 0; i<size;i++){array[i]  = 0; }
}

void PrintHeapArray( int array[], int size){
	int i;

	cout << "Org Heap Array:[";
	for ( i = 0; i<size-1;i++){ cout << array[i] << ","; }
	cout << array[i] << "]" << endl;
}