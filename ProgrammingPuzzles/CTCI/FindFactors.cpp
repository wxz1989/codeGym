#include <iostream>       // std::cout
#define MAX_VALUES 100

using namespace std;

#ifndef READ_INPUT_FROM_FILE
//#define READ_INPUT_FROM_FILE
#endif


void findSqrt(int value){

	if ( value <= 0 ){ return; }
	int i = 1;

	//while ((i*(i++)) < value );
	while ((i*i) < value ){ i++; }

	cout << "I is: " << i << endl;
	if( i*i == value ){
		cout << "Sqrt of " << value << " is ["<< i <<"]" << endl;
	} else {
		cout << "Can't find Sqrt of "<< value << "!" << endl;
	}
}


/*
	Using Babylonian Method of finding Square Root
*/
void FindSqrt(int value){

	if ( value <= 0 ){ return; }
	int i = 1;

	float x = value;
	float y = 1;
	float e = 0.00001;

	while ((x-y) > e){

		cout << "X:[" << x << "] Y:[" << y <<"]" << endl;
		x = (x+y)/2;
		y = value /x;
	}

	cout << "Sqrt of " << value << " is ["<< x <<"]" << endl;
}

//Time Complexity : O(logN)
//Space Complexity: O()
int findFactors( int factorArray[], int value){
	
	int index = 0;
	int divIndex = 1;

	int tempValue = value;
	factorArray[index++] = divIndex++;

	if ( value == 0 || value == 1 ){ 
		if ( value ==0 ){ factorArray[--index] = 0; }
		return index;
	}
	
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
		int value = (rand()%50);
		cout <<"=====================" << endl;
		cout << "FindingFactors[" << tc+1 <<"] of:" <<  value << endl;
		int factorsCount = findFactors(factorArray, value);
		PrintFactors(factorArray, factorsCount);
		ResetFactors(factorArray, factorsCount);
		cout <<"=====================" << endl;
	}
#endif

	findSqrt(625);
	FindSqrt(625);

	return 0;
}