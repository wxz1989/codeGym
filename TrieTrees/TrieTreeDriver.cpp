// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <time.h>
#include <limits>

#include "TrieTree.h"

#define SAMPLE_INPUT_SIZE 999
#define MAX_ARRAY_SIZE 100
#define ASCII_TABLE_SIZE 128
#define ASCII_SPACE_CHAR 32
#define WORD_LENGTH 25


#ifndef _USE_GET_LINE_
#define _USE_GET_LINE_
#endif

void Test_SampleInput(std::string);
void Test_RandomisedDataInput(std::string);
int Solve(std::string);

using namespace Tries;

TrieTree* pInstance =NULL;

void Test_SampleInput(std::string searchString){

	int test_cases = 0;
	int size= 0;

	std::string inputString;
	char A[MAX_ARRAY_SIZE] = { 0 };	

	pInstance  = TrieTree::GetInstance();
	if ( !pInstance ){  cout << "TrieTree failed!" << endl; return ; }
	
	freopen("TrieTree_Sample_Input.txt", "r", stdin);
	
#ifdef _USE_GET_LINE_
	//Converting String to Number using getline
	getline(cin, inputString);

	cout << "getline input strings:[" << inputString << "]" << endl;
	// This code converts from string to number safely.
	stringstream myStream(inputString);

	if ( myStream >> test_cases ){
		cout << "Test cases :[" << test_cases << "]" <<  endl;
	} else {
		cout << "Invalid number, please try again" << endl;
		return;
	}

	for (int tc = 0; tc < test_cases; tc++){
		
		getline(cin , inputString);
		cout << "Read String:[" << inputString << "]" << endl;
		pInstance->AddWord(inputString);
	}
	int Ans = Solve(searchString);	
/*	inputString.clear();
	cout << "Last CIN String:[" << inputString << "]" << endl;
*/	fclose(stdin);
#else 
	//std::cin >> test_cases;
	//cout << "Read TCs:[" << test_cases << "]" << endl;
	inputString = "r";
	while(std::cin>>inputString)  {
		cout << "Read String:[" << inputString << "]" << endl;
		pInstance->AddWord(inputString);
	}
	int Ans = Solve(searchString);
	std::cin >> inputString;

#endif

}


void Test_RandomisedDataInput(std::string searchString){

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


	cout << "InputData Size:[" << size <<"]" << endl;
	for (int i = 0; i< size; i++){

		//Word length
		int wordLength = rand() % WORD_LENGTH;

		for ( int j = 0;j < wordLength;j++){
			//Word's Chracters
			int value = rand() % ASCII_TABLE_SIZE;
			//A[j] =  'a' + value;
			if ( value >= ASCII_SPACE_CHAR && value < ASCII_TABLE_SIZE)
				A[j] =  value;
			else {
				A[j] =  ' ';
			}
		}

		pInstance->AddWord(A);
		memset(A, 0, sizeof(char)*wordLength);
	}
	int Ans = Solve(searchString);
}


int Solve(std::string searchString){
	
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

	std::string searchString("a");
	cout << "Arg Count:" << argc << endl;

	if ( argc == 3 ) {
		if ( strlen(argv[2]) > 0 ){
			searchString.clear();
			searchString += argv[2];
		}
	}
	
	if (argc > 1){
		cout << "Arg :" << argv[1] << endl;
		if ( strcmp(argv[1], "0") == 0 ){
			Test_SampleInput(searchString);
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput(searchString);
		}
		else {
			Test_SampleInput(searchString);
		}
	}
	else {
		Test_SampleInput(searchString);
	}
	return 0;
}
