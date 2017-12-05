#adding driver program code in comments at the end
#include <iostream>

using namespace std;

#define MAX_ELEMENTS 10

class SNodeWithMin{
public:	
	int value;
	int minSoFar;
};

class MinStack{
	SNodeWithMin* pStackArray;
	int top;
public:
	MinStack(){
		top = 0;
		pStackArray = new SNodeWithMin[MAX_ELEMENTS];
	}
	void Push(int value){
		if ( top < MAX_ELEMENTS ){
			SNodeWithMin* pTemp = new SNodeWithMin();
			pTemp->value = value;

			//cout << " Val:[" << value <<"]PeekMin:[" << Peek().minSoFar << "]" <<endl ;
			int min = findMin(value, Peek().minSoFar);
			pStackArray[top].value = value;
			if ( top == 0 ){
				pStackArray[top].minSoFar = value;
			}
			else {
				pStackArray[top].minSoFar = min;
			}
			top += 1;
		}
	}
	void Pop(){
		pStackArray[top].value = -1;
		pStackArray[top--].minSoFar = 999999999;
		if ( top <=0 ){ top = 0; }
	}
	SNodeWithMin Peek(){
		//cout << "Called Peek:[" << pStackArray[top].value << "]MinSoFar:[" << pStackArray[top].minSoFar << "]" << endl;
		return pStackArray[top-1];
	}

	static int findMin (int v1, int v2){
		return ((v1 < v2)? v1 : v2);
	}

	void Print(){
		cout << "Top:["<< top << "]Stack:"  << endl;
		for ( int i =0; i< top ; i++){
			cout <<"V:["<<pStackArray[i].value << "] Min:[" << pStackArray[i].minSoFar <<"]" << endl;
		}	
	}
};

/* Driver program with Randomized data input for test purpose
#include "StackWithMin.h"

//#define MAX_ARRAY_SIZE 50

//void Test_SampleInput();
void Test_RandomisedDataInput();

void Test_RandomisedDataInput(){

	MinStack stkObj ;
	
	//int A[MAX_ELEMENTS] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(NULL));
	size = rand() % 20;
	srand(time(NULL));

	for (int i = 0; i< size; i++){
		int value = rand() % 50;
		//A[i] = value;
		stkObj.Push(value);
	}
	stkObj.Print();
}


int main(){

	/*MinStack stkObj ;

	stkObj.Push(8);
	stkObj.Push(5);
	stkObj.Push(2);
	stkObj.Push(6);
	stkObj.Push(1);
	stkObj.Push(3);

	cout << "Peek Test1:"  << stkObj.Peek().value << endl;
	stkObj.Pop();
	cout << "Peek Test2:"  << stkObj.Peek().value << endl;
	stkObj.Pop();
	cout << "Peek Test3:"  << stkObj.Peek().value << endl;
	stkObj.Pop();

	stkObj.Print(); *//* comment ends

	Test_RandomisedDataInput();

	return 0;
}
*/
