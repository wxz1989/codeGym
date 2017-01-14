#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void ReversePtr(char** cPtr, int length, int cur);
void ReverseArr(char* cPtr, int length, int cur);

void ReverseArr(char* cPtr, int length, int cur){
	if ( cPtr == NULL ){
		return;
	}

	if ( length <= 0 ) { return; }
	if ( cur >= length) { return; }

	ReverseArr(cPtr, length, cur+1);
	if( cur >= length/2 ){
		char temp = cPtr[cur];
		cPtr[cur] = cPtr[(length-1) - cur];
		cPtr[(length-1) - cur] = temp;

	}
	return;
}

void ReversePtr(char** cPtr, int length, int cur){

	if ( cPtr == NULL && *cPtr == NULL ){
		return;
	}

	if ( length <= 0 ) { return; }
	if ( cur >= length) { return; }

	ReversePtr(cPtr, length, cur+1);

	if( cur >= length/2 ){
		char temp = (*cPtr)[cur];

		(*cPtr)[cur] = (*cPtr)[(length-1) - cur];

		(*cPtr)[(length-1) - cur] = temp;

	}


	return;
}

int main(int argc, char* argv[]){

	//char array[10] = "exit";
	char* stringPtr =  NULL;
	int stringLen = 0;
	
	if ( argc > 1){
		stringLen = strlen(argv[1]);
		stringPtr = new char[stringLen];
		strncpy(stringPtr, argv[1], stringLen );	
	} else {
		char testString[] = "(EMPTY)"; 
		stringLen = strlen(testString);
		stringPtr = new char[stringLen];
		strncpy(stringPtr, testString, stringLen);
	}
	ReversePtr(&stringPtr, stringLen, 0);
	cout << "Reverse String:" << stringPtr <<endl;

	ReverseArr(stringPtr, stringLen, 0);
	cout << "Re-Reverse String:" << stringPtr <<endl;

	delete [] stringPtr;
	stringPtr = NULL;
	return 0;
}