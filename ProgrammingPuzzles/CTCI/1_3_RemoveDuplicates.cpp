#include <iostream>
#include <stdlib.h>
#include <string.h>


using namespace std;

int dupFound = 0;

void Print(char inputArr[]);
void RemoveDuplicate(char* inputArr, int length);

void Print(char inputArr[]){
	int length = strlen(inputArr);
	cout << "Length: "<< length <<endl;
	for( int i = 0; i< length;i++){
		cout << inputArr[i] <<" " ;
	}
	cout << endl;
}

/*
1. Complexity of this function is : n^2 (n Square). 
2. Every ith element is compared against other n-i elements and hence for every iteration, (n*n-1) comparisions are made.
3. e.g
inputStr = "TEST"
n = 4
i = 0, j = [1...3] => 0 compared to other 3 elements. => n*n-1
i = 1, j = [2...3] => 1 compared to other 2 elements. => n*n-1
i = 2, j = [3...3] => 2 compared to other 1 elements. => n*n-1
i = 3, j = [4] => INVALID
*/
void RemoveDuplicate(char* inputArr, int length){

	for( int i = 0; i< length;i++){
		for ( int j = i+1; j< length;j++){

			int offset = 0;
			if ( inputArr[j] >='a' && inputArr[j]<='z'){
				offset = inputArr[j]  - 'a';
			} else  if ( inputArr[j] >='A' && inputArr[j]<='Z'){
				offset = inputArr[j]  - 'A';
			}

			char compCap = 'A' + offset;
			char compSmall = 'a' + offset;

			if ( inputArr[i] == inputArr[j] ||
				inputArr[i] == compSmall || 
				inputArr[i] == compCap){
				inputArr[j] = -(i+1);
			}
		}
	}
}


int main(int argc, char* argv[]){


	char* pInputArray = NULL;
	int strLen = 0;

	if ( argc > 1 ) {
		strLen = strlen(argv[1]);
		pInputArray = new char[strLen];
		strncpy(pInputArray, argv[1], strLen);
	} else {
		char testString[] = "(EMPTY)";
		strLen = strlen(testString);
		pInputArray = new char[strLen+1];
		strncpy(pInputArray, testString, strLen);
	}

	Print(pInputArray);
	RemoveDuplicate(pInputArray, strLen);
	Print(pInputArray);

	delete [] pInputArray;
	pInputArray = NULL;
	return 0;
}