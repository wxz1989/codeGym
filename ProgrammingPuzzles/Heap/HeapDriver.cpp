#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Heap.h"

using namespace std;

void PrintHeapArray(int arrayp[], int size);
void ResetHeapArray(int myArray[], int sizeOfHeap);

void ResetHeapArray(int array[], int size){
	for (int i = 0; i<size; i++){ array[i] = 0; }
}

void PrintHeapArray(int array[], int size){
	int i;
	if ( size  <= 0 ){ cout<< "Error:Invalid Heap Size!" << endl; return; }
	cout << "Org Heap Array[" << size << "]:[";
	for (i = 0; i<size - 1; i++){ cout << array[i] << ","; }
	cout << array[i] << "]" << endl;
}

void Test_SampleInput(Heap& heapArg);
void Test_RandomisedDataInput(Heap& heapArg);

void Test_SampleInput(Heap& heapArg){

	int myArray[MAX_HEAP_SIZE] = { 0 };
	int test_cases = 0;
	int sizeOfHeap = 0;

	freopen("HeapSampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){

		cin >> sizeOfHeap;

		//mHeap.SetHeapSize(sizeOfHeap);
		for (int i = 0; i < sizeOfHeap; i++){
			cin >> myArray[i];
			//heapArg.Add(myArray[i]);
		}
		//mHeap.SetHeapSize(sizeOfHeap);
		cout << "# " << tc + 1 << endl;
		heapArg.BuildHeap(myArray, sizeOfHeap);


		PrintHeapArray(myArray, heapArg.GetHeapSize());		//Because Add is not calld priot to Build Heap 
		//heapArg.PrintHeap();
		std::string stringHeap= heapArg.ToString();
		cout <<stringHeap << endl;

		heapArg.HeapSort();
		//heapArg.TestHS();

		heapArg.Clear();
		ResetHeapArray(myArray, heapArg.GetHeapSize());
	}
}
void Test_RandomisedDataInput(Heap& heapArg){

	int myArray[MAX_HEAP_SIZE] = { 0 };
	int sizeOfHeap = 0;

	srand(time(NULL));
	sizeOfHeap = rand() % 50;
	srand(time(NULL));

	//mHeap.SetHeapSize(sizeOfHeap);

	for (int i = 0; i< sizeOfHeap; i++){
		int heapValue = rand() % 100;
		myArray[i] = heapValue;
		heapArg.Add(myArray[i]);
	}

	cout << "========================" << endl;
	PrintHeapArray(myArray, heapArg.GetHeapSize());
	//heapArg.BuildHeap(myArray, sizeOfHeap);
	//heapArg.PrintHeap();
	//heapArg.Clear();
	//ResetHeapArray(myArray, sizeOfHeap);

	
	std::string stringHeap= heapArg.ToString();
	cout <<stringHeap << endl;

	heapArg.HeapSort();
	heapArg.Clear();
}

int main(int argc, char* argv[]){

	Heap mHeap(Heap::MIN_HEAP);
	mHeap.Init();

	cout << "Arg Count:" << argc << endl;
	if (argc == 2){
		if (strcmp(argv[1], "0") == 0){
			Test_SampleInput(mHeap);
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput(mHeap);
		}
		else {
			Test_SampleInput(mHeap);
		}
	} else if ( argc == 3 ){
		if (strcmp(argv[1], "0") == 0)	 {  // Heap: Test Mode(0: for SampleInput, 1: RandomizedInput)
			if (strcmp(argv[2], "0") == 0){		// Heap: HeapType(0: for MinHeap, 1: MaxHeap)
				mHeap.SetHeapType(Heap::MIN_HEAP);
			} else if (strcmp(argv[2], "1") == 0){ 
				mHeap.SetHeapType(Heap::MAX_HEAP);
			}
			Test_SampleInput(mHeap);
		}
		else if (strcmp(argv[1], "1") == 0){
			if (strcmp(argv[2], "0") == 0){		// Heap: HeapType(0: for MinHeap, 1: MaxHeap)
				mHeap.SetHeapType(Heap::MIN_HEAP);
			} else if (strcmp(argv[2], "1") == 0){ 
				mHeap.SetHeapType(Heap::MAX_HEAP);
			}
			Test_RandomisedDataInput(mHeap);
		}
		else {
			Test_SampleInput(mHeap);
		}
	}
	return 0;
}
