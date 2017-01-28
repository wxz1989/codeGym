#include <iostream>       // std::cout
#define MAX_VALUES 100

using namespace std;

#ifndef READ_INPUT_FROM_FILE
//#define READ_INPUT_FROM_FILE
#endif

int findFactors( int factorArray[], int value){
	
	if ( value == 0 ){ return 0;}

	int index = 0;
	int divIndex = 1;

	int tempValue = value;
	factorArray[index++] = divIndex++;

	if ( value == 1 ){ return index; }
	
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

	if ( size >= MAX_VALUES ){ 
		cout << "Out of bounds, can't show factors more than "<<  MAX_VALUES << " !" << endl;
		size = MAX_VALUES;
	}
	for ( int i = 0;i < size; i++){ factorArr[i] = 0 ; }
}

void PrintFactors(int factorArr[], int size){
	
	if ( size <=0  ){
		cout <<"Factors:["<<0<<"]:[0]" << endl;
		return; 
	}
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
		cout <<"=====================" << endl;
		cout << "FindingFactors[" << tc+1 <<"] of:" <<  value << endl;
		int factorsCount = findFactors(factorArray, value);
		PrintFactors(factorArray, factorsCount);
		ResetFactors(factorArray, factorsCount);
		cout <<"=====================" << endl;
	}
#else
	srand(time(NULL));
	test_cases = (rand()%10);
	srand(time(NULL));
	for ( int tc = 0; tc< test_cases;tc++){
		//call your functions with random value
		int value = (rand()%9999);
		cout <<"=====================" << endl;
		cout << "FindingFactors[" << tc+1 <<"] of:" <<  value << endl;
		int factorsCount = findFactors(factorArray, value);
		PrintFactors(factorArray, factorsCount);
		ResetFactors(factorArray, factorsCount);
		cout <<"=====================" << endl;
	}
#endif
	return 0;
}