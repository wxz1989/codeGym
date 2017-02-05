#include "Heap.h"

using namespace std;

void PrintHeapArray( int arrayp[], int size);
void ResetHeapArray(int myArray[],int sizeOfHeap);

Heap::Heap(){
	pHeapArray = NULL;
	mHeapType = Heap::MIN_HEAP;
	heapSize = 0;
	heapCapacity = INT_CAPACITY;
	//memset(pHeapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}
Heap::Heap(HeapType hType, size_t cap){

	pHeapArray = NULL;
	mHeapType = hType;
	heapCapacity = cap;
	heapSize = 0;
	//memset(pHeapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}

Heap::~Heap(){

	delete [] pHeapArray;
}

void Heap::Init(void){
	pHeapArray = new int[heapCapacity];
	memset(pHeapArray, 0, sizeof(int)* heapCapacity);
}
void Heap::Clear(void){
	memset(pHeapArray, 0, sizeof(int)* heapSize);
	SetHeapSize(0);
}

void Heap::Add(int value){

	pHeapArray[heapSize+1] = value;
	heapSize++;
	if ( heapSize >= heapCapacity){
		Resize();
	}
	if ( heapSize > 1 ){  Heapify(); }	
}
bool Heap::Remove(int value){
	return false;
}
bool Heap::Update(int valueToUpdate, int newValue){
	return false;
}

void Heap::SetHeapSize(size_t size){
	heapSize = size;
}

size_t Heap::GetHeapSize(void){
	return heapSize;
}

void Heap::SetHeapType(int t){
	mHeapType = (HeapType)t;
}

int Heap::GetHeapType(void){
	return (HeapType)mHeapType;
}

bool Heap::IsValid(int childIndex /*, int parent*/){

	bool retValue = false;

	if( childIndex <= heapSize  /*&& parent <= heapSize*/ ){ retValue=true; }
	else { retValue = false; }

	return retValue;
}

int Heap::GetSwapIndex(int lIndex, int rIndex, int parent){

	int index = INVALID;
	int pivotIndex = INVALID;

	//Missed one condition : If Only one of the Child exists and not two?
	if ( mHeapType == Heap::MIN_HEAP ){
		if ( IsValid(lIndex) && IsValid(rIndex)){
			int left = pHeapArray[lIndex];
			int right = pHeapArray[rIndex];

			if ( left < right){
				index = lIndex;
			} else {
				index = rIndex;
			}
		} else if ( IsValid(lIndex)){
			index = lIndex;
		} else if ( IsValid(rIndex)){
			index = rIndex;
		}

		if ( index != INVALID ){ if( pHeapArray[parent] > pHeapArray[index] ){ pivotIndex=index; } }
	} else {
		if ( IsValid(lIndex) && IsValid(rIndex)){
			int left = pHeapArray[lIndex];
			int right = pHeapArray[rIndex];
			
			if ( left > right){
				index = lIndex;
			} else {
				index = rIndex;
			}
		} else if ( IsValid(lIndex)){
			index = lIndex;
		} else if( IsValid(rIndex)){
			index = rIndex;
		}
		if ( index != INVALID ){ if( pHeapArray[parent] < pHeapArray[index] ){ pivotIndex=index; }}
	}
	return pivotIndex;
}

//ToDo:Implement Min using Delete Root from MinHeap and Max using Delete Root in MaxHeap
int Heap::Delete(){ 

	if ( heapSize == 0 ) { cout << "Error: Empty Heap" << endl; return INVALID;}

	int minValue = pHeapArray[1];
	//for( int i = 1; i<heapSize+1; i++){ pHeapArray[i] = pHeapArray[i+1]; }

	pHeapArray[1] = pHeapArray[heapSize];
	pHeapArray[heapSize] = 0;

	heapSize--;

	Heapify();

	return minValue; 
}

int Heap::GetSize(){ return heapSize; }

//Purpose of this function is to Copy value from the given HeapArray and use it for applying basic Heap algorithm HEAPIFY
void Heap::BuildHeap(int a[], int N){
	if ( N > heapCapacity){ Resize(); }
	for (int i = 0; i< N; i++){ pHeapArray[i + 1] = a[i]; }
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
		if (mHeapType == MIN_HEAP){ 
			if ( pHeapArray[1] > pHeapArray[2] ) {  bSwap = true; }
		} else {
			if ( pHeapArray[1] < pHeapArray[2] ) {  bSwap = true; }
		}
		if ( bSwap ){
			int temp = pHeapArray[1];
			pHeapArray[1] = pHeapArray[2];
			pHeapArray[2] = temp;
		}
	}
}

void Heap::HeaptifyUtil(int parentIndex){

	if ( parentIndex <=0 || parentIndex > heapSize  ){ return; }

	int pivot = INVALID;

	int lCIndex = 2 * parentIndex;
	int rCIndex = (2 * parentIndex) + 1;

	int parent = pHeapArray[parentIndex];
	int lChild = pHeapArray[lCIndex];
	int rChild = pHeapArray[rCIndex];

	// for min heap 
	// MINHEAP RULE : Check if lChild index is LESS or EQUAL to heapSize
	//Also check for Min Heap Property
	// If current parent and leftChld relation violates Min Heap Property.
	// If it does than select the curent Parent as Pivot and swap Parent and Child values.

	pivot = GetSwapIndex(lCIndex, rCIndex, parentIndex);
	if ( pivot >0 && pivot <=heapSize ){
		int temp = pHeapArray[parentIndex];
		pHeapArray[parentIndex] = pHeapArray[pivot];
		pHeapArray[pivot] = temp;
		HeaptifyUtil(pivot);
	}
	return;
}

std::string Heap::ToString(void){
	std::string retValue("");
	
	char heapString[] = {0};

	sprintf(heapString, "%s", "Heap:[");
	retValue.append(heapString);

	int i;
	for (i = 1; i < heapSize; i++){
		sprintf(heapString, "%d%c", pHeapArray[i], ',');
		retValue.append(heapString);
	}
	sprintf(heapString, "%d%c", pHeapArray[i], ']');
	retValue.append(heapString);

	return retValue;
}

void Heap::PrintHeap(void){
	
	std::cout << "Size:" << heapSize << std::endl;
	std::cout << "Heap:[";
	int i;
	for (i = 1; i < heapSize; i++){
		std::cout << pHeapArray[i] << ",";
	}
	std::cout << pHeapArray[i] << "]" <<  std::endl;
}

void Heap::HeapSort(void){

	cout << "HeapSort>>Enter" << endl;
	int start=1, end =heapSize;

	int index = 0;
	int* sorted= new int[heapSize];

	while ( GetSize() > 0 ){
		int min = INVALID;
		min = Delete();
		if( min != INVALID ){
			sorted[index++] = min;
		}
	}

	cout << "HeapSort:[";
	int i;
	for (i = 0; i < index-1;i++){
		cout << sorted[i] << ", ";
	}
	cout << sorted[i] << "] " << endl;

	delete [] sorted;
	sorted = NULL;
	cout << "HeapSort<<Exit" << endl;
}

void Heap::Resize(void){
	int* pBackUp = new int[2*heapCapacity];
	memcpy(pBackUp, pHeapArray, sizeof(int)* heapSize);

	delete [] pHeapArray;
	pHeapArray = pBackUp;
	heapCapacity *=2; 
}

void Heap::SetHeapCapacity(size_t cap){
	heapCapacity = cap;
}
size_t Heap::GetHeapCapacity(void){
	return heapCapacity;
}

