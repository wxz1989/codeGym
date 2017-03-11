#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100
#define ALPHABET_RANGE 26

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
bool Solve(char inputArr[], int length);

std::string toBinary(unsigned int n)	//From StackOverFlow 
{
    std::string r;
    while(n!=0) {
    	r =r+(n%2==0 ?"0":"1");
    	n/=2;
    }
    return r;
}

bool Solve(char inputArr[], int length){

	bool dupFound = false;
	if( length <=0 || length > 128 ){ return 0;	}  //Assumption is only ASCII characters are there in the given input string


	int i = 0, checker = 0;

	while ( inputArr[i]){
		int diff =0;
		if ( inputArr[i] >= 'A' && inputArr[i] <= 'Z'){
			diff = inputArr[i] - 'A';
		} else if ( inputArr[i] >= 'a' && inputArr[i] <= 'z'){
			diff = inputArr[i] - 'a';
		}

		if ( (checker & ( 1 << diff)) > 0 ){
			dupFound = true;
			break; 
		} else {
			checker |= ( 1 << diff);
		}
		i++;
	}
	//cout<< "Name:[" << inputArr << "]=>Code[" <<checker << "] & Binary[" << toBinary(checker)<< "]" << endl;
	return dupFound;
}

void Test_SampleInput(){

	char A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	std::string inputString;

	freopen("IsUniqueCharsSampleInput.txt", "r", stdin);
	cin >> test_cases;

	getline(cin , inputString);
	for (int tc = 0; tc < test_cases; tc++){
		//cin >> A;
		getline(cin , inputString);	
		int size =inputString.size();
		//while (A[size++]);
		cout << "Input:[" << inputString.c_str() << "]"  << endl;
		cout << "# " << tc + 1 <<" " << Solve((char*)inputString.c_str(),size) << endl;
	}
}
void Test_RandomisedDataInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(NULL));
	size = rand() % 10;
	srand(time(NULL));

	for (int i = 0; i< size; i++){
		int value = rand() % ALPHABET_RANGE;
		cout<< "Value[" <<value << "] & Binary[" << toBinary(value)<< "]" << endl;
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
