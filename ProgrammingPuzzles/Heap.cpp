#include <iostream>
#include <memory.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1000

class Heap{

public:
	Heap();
	Heap(int t);
	
private:
	int currentIndex;
	
	enum HeapType{
		MIN_HEAP = 0,
		MAX_HEAP,
	};
	int heapArray[MAX_HEAP_SIZE];

	HeapType type;
	int size;

public:
	void add(int value);
	bool remove(int value);
	bool update(int valueToUpdate, int newValue);

	void buildHeap(int a[], int N);
	void heapify();
	void heaptifyUtil(int index);	
	int getMin();
	int getMax();
	int getSize();

	std::string toString();
};

Heap::Heap(){
	currentIndex = 0;
	type=(HeapType)0;
	size=0;
	memset(heapArray, 0, sizeof(int) * MAX_HEAP_SIZE);
}
Heap::Heap(int t){
	type = type;
}

void Heap::add(int value){
	heapArray[currentIndex++] = value;
	heapify();
	size++;
}
bool Heap::remove(int value){
	return false;
}
bool Heap::update(int valueToUpdate, int newValue){
	return false;
}

void Heap::heaptifyUtil(int iIndex){
	int pivot = 0;
	int value = heapArray[iIndex];
	int left = 2*iIndex;
	int right = (2*iIndex)+1;

	if ( type == MIN_HEAP){
		if ( left < size && heapArray[left] < heapArray[iIndex]){
			pivot = left;
		}
		if ( right < size && heapArray[right] < heapArray[iIndex]){
			pivot = right;
		}
	} else {
		if ( left < size && heapArray[left] > heapArray[iIndex]){
			pivot = left;
		}
		if ( right < size && heapArray[right] > heapArray[iIndex]){
			pivot = right;
		}
	}

	//Swap Smallest with iIndex...
	int temp = heapArray[iIndex];
	heapArray[iIndex] = heapArray[pivot];
	heapArray[pivot] = temp;

	heaptifyUtil(pivot);
}
void Heap::buildHeap(int a[], int N){
	for( int i = 0; i< N;i++){
		heapArray[i+1] = a[i];
	}
	heapify();
}
void Heap::heapify(){

	for( int  i = size -1; i>0;i--){
		heaptifyUtil(i);	
	}
}
int Heap::getMin(){
	return 0;
}
int Heap::getMax(){
	return 0;
}
int Heap::getSize(){
	return size;
}
std::string Heap::toString(){
	std::string retValue;
	/*int index = 0;
	
	retValue.append("[");
	char buffer[100];
	for (index = 1; index < size; index++){
		sprintf(buffer, "%d,", heapArray[index]);
		retValue.append(buffer);
	}
	sprintf(buffer, "%d]", heapArray[index]);
	retValue.append(buffer);*/
	std::cout <<"Heap Contnet"<<std::endl;
	std::cout <<"Heap Size: "<< size << std::endl;
	for (int i = 1; i < size; i++){
		std::cout<< i;
	}
	std::cout<<std::endl;
	return retValue;
}


int main(){

	Heap mHeap(0);
	int myArray[7] = {4,5,1,6,7,3,2};
	mHeap.buildHeap(myArray, 7);

	mHeap.toString();

	return 0;
}