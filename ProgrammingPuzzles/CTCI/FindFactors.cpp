#include <iostream>       // std::cout
#define MAX_VALUES 100

using namespace std;

#ifndef READ_INPUT_FROM_FILE
//#define READ_INPUT_FROM_FILE
#endif

int findFactors( int factorArray[], int value){
	
	if ( value == 0 ){ return 0;}
	if ( value == 1 ){ 
		factorArray[0] = 1; 
		return 1; 
	}

	int index = 0;
	int divIndex = 1;

	int tempValue = value;
	factorArray[index++] = divIndex++;
	
	while (tempValue >0 && divIndex <= tempValue ){
		if ( tempValue % divIndex == 0 ){
			tempValue /= divIndex;
			factorArray[index++] = divIndex;
		} else{
			divIndex++;
		}
	}	
	//cout << "Index:["<< index <<"]" <<endl;
	if ( index > 2 ){ factorArray[index++] = value; }
	return index;
}

void ResetFactors(int factorArr[], int size){

	if ( size >= MAX_VALUES ){size = MAX_VALUES;}
	for ( int i = 0;i < size; i++){ factorArr[i] = 0 ; }
}

void PrintFactors(int factorArr[], int size){
	
	if ( size <=0  ){ return; }
	cout <<"Factors:["<<size<<"]:[";

	int i = 0;
	for ( i = 0;i < size-1; i++){
		cout << factorArr[i] << ", " ;
	}
	cout << factorArr[i] << "]"<<endl;
}

int main ()
{
	int test_cases = 0;
	int factorArray[MAX_VALUES] = {0};

#ifdef READ_INPUT_FROM_FILE
	freopen("FindFactors_Input.txt", "r", stdin);
	cin >> test_cases;

	for ( int tc = 0; tc< test_cases;tc++){
		int value=0;
		cin >> value;
		//Call your function
		int factorsCount = findFactors(factorArray, value);
		PrintFactors(factorArray, factorsCount);
		ResetFactors(factorArray, factorsCount);
	}
#else
	srand(time(NULL));
	//call your functions with random value
	int value = (rand()%100);
	cout << "Finding factors of:" << value << endl;
	int factorsCount = findFactors(factorArray, value);
	PrintFactors(factorArray, factorsCount);
#endif
	return 0;
}