// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <time.h>

#include "TrieTree.h"

#define SAMPLE_INPUT_SIZE 10
#define MAX_ARRAY_SIZE 100

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve();

TrieTree* pInstance =NULL;

void Test_SampleInput(){

	pInstance  = TrieTree::GetInstance();
	if ( !pInstance ){
		cout << "TrieTree failed!" << endl;
		return;
	}
	char A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	std::string inputString;

	freopen("TrieTree_Sample_Input.txt", "r", stdin);

	//Converting String to Number using getline
	getline(cin, inputString);

	// This code converts from string to number safely.
	stringstream myStream(inputString);
	if ( myStream >> test_cases ){
		cout << "Test cases :[" << test_cases << "]" <<  endl;
	} else {
		cout << "Invalid number, please try again" << endl;
	}

	for (int tc = 0; tc < test_cases; tc++){
		
		getline(cin , inputString);
		pInstance->AddWord((char*)inputString.c_str());
	}

	int Ans = Solve();
	/*std::string searchString;
	while((std::cin>>searchString))  {
		cout << "Read String:[" << searchString << "]" << endl;
	}*/
}
void Test_RandomisedDataInput(){

	pInstance = TrieTree::GetInstance();
	if ( !pInstance ){
		cout << "TrieTree failed!" << endl;
		return;
	}

	std::string inputString;
	char A[MAX_ARRAY_SIZE] = { 0 };
	int size = 0;

	//Test cases length
	srand(time(NULL));
	size = rand() % SAMPLE_INPUT_SIZE;


	//cout << "Size:[" << size <<"]" << endl;
	for (int i = 0; i< size; i++){

		//Word length
		int wordLength = rand() % MAX_SIZE;

		for ( int j = 0;j < wordLength;j++){
			//Word's Chracters
			int value = rand() % MAX_SIZE;
			A[j] =  'a' + value;
		}

		pInstance->AddWord(A);
		memset(A, 0, sizeof(char)*wordLength);
	}
	int Ans = Solve();
}


int Solve(){
	std::string searchString("a");
	cout << "************** SEARCH ***************"<< endl ;
	cout << "Search string is: [" << searchString << "]" <<  endl;
	cout << "************** SEARCH RESULTS ***************"<< endl ;

	if ( pInstance->FindWordByPrefix(searchString) == -1 ){
		cout << "No results found" <<  endl;
	}
	cout << "************** SEARCH ENDS ******************"<< endl ;
	return 0;
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
