#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Heap.h"

using namespace std;

void PrintHeapArray( int arrayp[], int size);
void ResetHeapArray(int myArray[],int sizeOfHeap);

void ResetHeapArray(int array[], int size){
	for ( int i = 0; i<size;i++){array[i]  = 0; }
}

void PrintHeapArray( int array[], int size){
	int i;
	cout << "Org Heap Array[" << size << "]:[" ;
	for ( i = 0; i<size-1;i++){ cout << array[i] << ","; }
	cout << array[i] << "]" << endl;
}

int main(){

	Heap mHeap(Heap::MIN_HEAP);
	mHeap.Init();

	int myArray[MAX_HEAP_SIZE] = { 0 };
	int test_cases = 0;
	int sizeOfHeap = 0;

#ifdef READ_DATA_FROM_FILE
	freopen("HeapSampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){
		
		cin >> sizeOfHeap;

		//mHeap.SetHeapSize(sizeOfHeap);
		for (int i = 0; i < sizeOfHeap; i++){
			cin >> myArray[i];
			mHeap.Add(myArray[i]);
		}
		//mHeap.SetHeapSize(sizeOfHeap);
		cout <<"# "<< tc+1 << endl;
		PrintHeapArray(myArray, mHeap.GetHeapSize());
		//mHeap.BuildHeap(myArray, sizeOfHeap);
		//mHeap.PrintHeap();
		cout << mHeap.ToString() << endl;
		
		//mHeap.GetHeapType() == 0 ? mHeap.SetHeapType(1) : mHeap.SetHeapType(0);
		/*while ( mHeap.GetSize() > 0 ){
			int min = INVALID;
			min = mHeap.Delete();
			if( min != INVALID ){
				cout << "Min: " << min << endl;
			} else {
				cout << "Invalid min" << endl;
			}
			//mHeap.PrintHeap();
			cout << mHeap.ToString() << endl;
		}*/

		mHeap.HeapSort();

		mHeap.Clear();
		ResetHeapArray(myArray, mHeap.GetHeapSize());
	}
#else
	srand(time(NULL));
	sizeOfHeap = rand()%10;
	srand(time(NULL));

	//mHeap.SetHeapSize(sizeOfHeap);

	for ( int i = 0; i< sizeOfHeap;i++){
		int heapValue = rand()%30;
		myArray[i] = heapValue;	
		mHeap.Add(myArray[i]);
	}

	cout <<"========================"<< endl;
	PrintHeapArray(myArray, mHeap.GetHeapSize());
	//mHeap.BuildHeap(myArray, sizeOfHeap);
	mHeap.PrintHeap();
	//mHeap.Clear();
	//ResetHeapArray(myArray, sizeOfHeap);

	mHeap.HeapSort();
	mHeap.clear();

	/*
	while ( mHeap.GetSize() > 0 ){
		int min = INVALID;
		min = mHeap.Delete();
		if( min != INVALID ){
			cout << "Min: " << min << endl;
		} else {
			cout << "Invalid min" << endl;
		}
		//mHeap.PrintHeap();
		cout << mHeap.ToString() << endl;
	}
	*/


#endif
	return 0;
}
