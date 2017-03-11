#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve();

int Solve(){
	return 0;
}

void Test_SampleInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	freopen("SampleInput.txt", "r", stdin);
	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){

		cin >> size;

		for (int i = 0; i < size; i++){
			cin >> A[i];
		}


		int Ans = Solve();

		cout << "# " << tc + 1 <<" " << Ans << endl;
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
