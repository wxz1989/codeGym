#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <list>
#include <set>

typedef char ArrayType;

#define MAX_ARRAY_SIZE 256

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve(char* arr, int size);

void PrintArray(ArrayType* pArr, int size ){
	cout << "Array:[";
	for ( int i = 0; i< size;i++){
		cout << pArr[i]<< " ";
	}
	cout << "]" <<endl;
}
void PrintMapArray(int* pArr, int size ){
	cout << "MapArray:[";
	for ( int i = 0; i< size;i++){
		cout << pArr[i]<< " ";
	}
	cout << "]" <<endl;
}

void PrintSet(std::list<ArrayType>  s){
	cout << "List:[";
	for ( std::list<char>::iterator it=s.begin();  it != s.end();++it){
		cout << *it << " ";
	}
	cout <<"]" << endl;
	
}

int Solve(char* arr, int size){

	int mapArray[MAX_ARRAY_SIZE] = {0};
	for ( int i = 0; i< MAX_ARRAY_SIZE ;i++){ mapArray[i] = 0; }

	PrintArray(arr, size);
	list<char> fnrcList;
	std::list<char>::iterator it = fnrcList.end();
	for ( int i = 0; i< size;i++){
		if( (arr[i] >= 'A' && arr[i] <='Z') || (arr[i] >= 'a' && arr[i] <='z') ) {
			int iIndex =  abs ( arr[i] - 'a');

			if ( mapArray[iIndex] == 0 ){				//Visited for the first Time hance Print that character
				mapArray[iIndex] = 1;
				fnrcList.push_back(arr[i]);				
			}  else  if ( mapArray[iIndex] ==1 ){		//Being visited for the second time(hence mark it as -1  and remove from List)
				mapArray[iIndex] = -1;
				fnrcList.remove(arr[i]);
			} 
			if ( fnrcList.size() == 0 ){  cout << -1 << " "; } 
			else { it=fnrcList.begin();  cout << *it << " " ; }
			PrintMapArray(mapArray, size);
			PrintSet(fnrcList);
		}
	}
	return 0;
}

void Test_SampleInput(){

	char A[MAX_ARRAY_SIZE] = { 0 };	
	

	int test_cases = 0;
	int size= 0;

	freopen("FNRCSampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){

		for (int i = 0; i < MAX_ARRAY_SIZE; i++){ A[i] = 0; }
		cin >> size;
		for (int i = 0; i < size; i++){
			cin >> A[i];
		}

		cout << "# " << tc + 1 <<" " << endl;
		int Ans = Solve(A, size);
		cout <<  endl;
	}
}
void Test_RandomisedDataInput(){

	ArrayType A[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(NULL));
	size = rand() % 10;
	srand(time(NULL));

	for (int i = 0; i< size; i++){
		int value = rand() % 30;
		A[i] = value;
	}
}

int main(int argc, char* argv[]){

	cout << "Arg Count:" << argc << endl;
	if (argc > 1){
		cout << "Arg :" << argv[1] << endl;
		if (strcmp(argv[1], "0") == 0){
			Test_SampleInput();
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput();
		}
		else {
			Test_SampleInput();
		}
	} else {
		Test_SampleInput();
	}
	return 0;
}
