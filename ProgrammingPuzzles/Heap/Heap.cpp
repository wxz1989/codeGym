#include "Heap.h"

using namespace std;

void PrintHeapArray( int arrayp[], int size);
void ResetHeapArray(int myArray[],int sizeOfHeap);

Heap::Heap(){
	mHeapType = Heap::MIN_HEAP;
	heapSize = 0;
	heapCapacity = INT_CAPACITY;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}
Heap::Heap(HeapType hType, size_t cap){
	mHeapType = hType;
	heapCapacity = cap;
	heapSize = 0;
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
}

void Heap::Clear(void){
	memset(heapArray, 0, sizeof(int)* MAX_HEAP_SIZE);
	SetHeapSize(0);
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

bool Heap::IsValid(int childIndex, int parent){

	bool retValue = false;

	if( childIndex <= heapSize  && parent <= heapSize ){ retValue=true; }
	else { retValue = false; }

	return retValue;
}

int Heap::GetSwapIndex(int lIndex, int rIndex, int parent){

	int index = -1;
	int pivotIndex = -1;

	int left = heapArray[lIndex];
	int right = heapArray[rIndex];
	if ( mHeapType == Heap::MIN_HEAP ){

		if ( left < right){
			index = lIndex;
		} else {
			index = rIndex;
		}
		if( heapArray[parent] > heapArray[index] ){ pivotIndex=index; }
	} else {

		if ( left > right){
			index = lIndex;
		} else {
			index = rIndex;
		}

		if( heapArray[parent] < heapArray[index] ){ pivotIndex=index; }
	}
	return pivotIndex;
}

//ToDo:Implement Min using Delete Root from MinHeap and Max using Delete Root in MaxHeap
int Heap::Delete(){ 

	if ( heapSize == 0 ) { cout << "Error: Empty Heap" << endl; return -1;}

	int minValue = heapArray[1];
	//for( int i = 1; i<heapSize+1; i++){ heapArray[i] = heapArray[i+1]; }

	heapArray[1] = heapArray[heapSize];
	heapArray[heapSize] = 0;

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
		if (mHeapType == MIN_HEAP){ 
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

	if ( parentIndex <=0 || parentIndex > heapSize  ){ return; }

	int pivot = INVALID;

	int lCIndex = 2 * parentIndex;
	int rCIndex = (2 * parentIndex) + 1;

	int parent = heapArray[parentIndex];
	int lChild = heapArray[lCIndex];
	int rChild = heapArray[rCIndex];

	// for min heap 
	// MINHEAP RULE : Check if lChild index is LESS or EQUAL to heapSize
	//Also check for Min Heap Property
	// If current parent and leftChld relation violates Min Heap Property.
	// If it does than select the curent Parent as Pivot and swap Parent and Child values.

	pivot = GetSwapIndex(lCIndex, rCIndex, parentIndex);
	if ( pivot >0 && pivot <=heapSize ){
		int temp = heapArray[parentIndex];
		heapArray[parentIndex] = heapArray[pivot];
		heapArray[pivot] = temp;
		HeaptifyUtil(pivot);
		//HeaptifyUtil(parentIndex);  
		//ToDo : Remove above call. Though by removing it results are inaccurate, 
		// Somehow I feel it's redundant and there should be some other way of doing it
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
		sprintf(heapString, "%d%c", heapArray[i], ',');
		retValue.append(heapString);
	}
	sprintf(heapString, "%d%c", heapArray[i], ']');
	retValue.append(heapString);

	return retValue;
}

void Heap::PrintHeap(void){
	
	std::cout << "Size:" << heapSize << std::endl;
	std::cout << "Heap:[";
	int i;
	for (i = 1; i < heapSize; i++){
		std::cout << heapArray[i] << ",";
	}
	std::cout << heapArray[i] << "]" <<  std::endl;
}

void Heap::HeapSort(void){
}

void Heap::Resize(void){
}



int main(){

	Heap mHeap(Heap::MAX_HEAP);

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
		while ( mHeap.GetSize() > 0 ){
			int min = -1;
			min = mHeap.Delete();
			if( min != -1 ){
				cout << "Min: " << min << endl;
			} else {
				cout << "Invalid min" << endl;
			}
			//mHeap.PrintHeap();
			cout << mHeap.ToString() << endl;
		}

		mHeap.Clear();
		ResetHeapArray(myArray, mHeap.GetHeapSize());
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
	mHeap.PrintHeap();
	//mHeap.Clear();
	//ResetHeapArray(myArray, sizeOfHeap);

	while ( mHeap.GetSize() > 0 ){
		int min = -1;
		min = mHeap.Delete();
		if( min != -1 ){
			cout << "Min: " << min << endl;
		} else {
			cout << "Invalid min" << endl;
		}
		//mHeap.PrintHeap();
		//cout << mHeap.ToString() << endl;
	}


#endif
	return 0;
}

void ResetHeapArray(int array[], int size){
	for ( int i = 0; i<size;i++){array[i]  = 0; }
}

void PrintHeapArray( int array[], int size){
	int i;
	cout << "Org Heap Array[" << size << "]:[" ;
	for ( i = 0; i<size-1;i++){ cout << array[i] << ","; }
	cout << array[i] << "]" << endl;
}