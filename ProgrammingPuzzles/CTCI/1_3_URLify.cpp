#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve(char inputArray[], int arrLength);

int Solve(char inputArray[], int arrLength){

	//cout <<"Enter [" << inputArray << "]" << endl;
	int newSize = 0, spaceCount = 0;
	if ( arrLength <= 0 ){ 	return 0; }

	//cout <<"Valid array Length: " <<arrLength <<  endl;

	int i =0, j =0;
	while ( inputArray[i++]){
		if ( inputArray[i] == ' ' ){
			spaceCount++;
		}
	}
	//cout <<"SpaceCount: " <<spaceCount <<  endl;

	if ( spaceCount > 0 ){
		newSize = (arrLength + (spaceCount*2))+1;
	}

	char* pNewArray = new char[newSize];
	memset(pNewArray, 0 , sizeof(char)* newSize);

	i=arrLength-1;
	j=newSize-1;
	//cout << "NewSize:" << newSize << endl;

	pNewArray[j--] ='\0';

	for (; i >=0 ;){
		//cout << "I:[" << i << "]" << "J:["<< j <<"]" << endl;
		if ( inputArray[i] == ' ' ){
			pNewArray[j] = '0';
			pNewArray[j-1] = '2';
			pNewArray[j-2] = '%';
			j -=3;
		} else {
			pNewArray[j--] = inputArray[i];
		}
		i--;
	}

	cout <<"URLified String:" << pNewArray << endl;

	delete pNewArray;
	pNewArray = NULL;
	return 0;
}

void Test_SampleInput(){

	char A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	std::string inputString;

	freopen("URLifySampleInput.txt", "r", stdin);
	cin >> test_cases;

	getline(cin , inputString);
	for (int tc = 0; tc < test_cases; tc++){
		//cin >> A;
		getline(cin , inputString);	
		int size =inputString.size();
		//while (A[size++]);
		cout << "InputString:[" << inputString.c_str() << "] Size:[" << size << "]" << endl;
		int Ans = Solve((char*)inputString.c_str(),size);
		cout << "# " << tc + 1 <<" " << Ans << endl;
	}
}
void Test_RandomisedDataInput(){

	cout << "******Not Supporeted for this Problem******" << endl;
	return;
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
