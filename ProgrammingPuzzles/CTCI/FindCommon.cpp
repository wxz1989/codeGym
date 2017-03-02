#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();

int Solve(int A[], int B[], int sA, int sB);

int Solve(int A[], int B[], int sA, int sB){
	if (sA <= 0 || sB <= 0){ return -1; }

	int matchCount = 0;

	int iA=0, iB = 0;
	//if (sA == sB)
	{
		for (iA = 0, iB = 0; iA<sA || iB<sA; ){
			//cout << "Index A:" << iA << " Index B:" << iB << endl;
			//cout << "Values of A :" << A[iA] << " Value of B:" << B[iB] << endl;
			if (A[iA] < B[iB]) {
				iA++;
				if ( iA >= sA){ 
					iA  -=1;
					iB++;
				}
			} else if (A[iA] > B[iB]){
				iB++;
				if ( iB >=sB){
					iB -=1;
					iA++;
				}
			} else {
				cout << "A:" << A[iA] << " B:" << B[iB] << endl;
				iA++;
				iB++;

				if ( iA >= sA){ 
					iA  -=1;
					iB++;
				}
				if ( iB >=sB){
					iB -=1;
					iA++;
				}
				++matchCount;
			}		
		}
	}
	return matchCount;
}

void Test_SampleInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };
	int B[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int sA= 0;
	int sB = 0;

	freopen("SampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){

		cin >> sA;
		cin >> sB;
		for (int i = 0; i < sA; i++){
			cin >> A[i];
		}

		for (int i = 0; i < sB; i++){
			cin >> B[i];
		}

		int Ans = Solve(A, B, sA, sB);

		cout << "# " << tc + 1 <<" " << Ans << endl;
	}
}
void Test_RandomisedDataInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };
	int B[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int sA = 0;
	int sB = 0;

	srand(time(NULL));
	sA = rand() % 10;
	srand(time(NULL));

	for (int i = 0; i< sA; i++){
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
