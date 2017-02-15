#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HashTable.h"

using namespace std;

void Test_SampleInput(HashTable& heapArg);
void Test_RandomisedDataInput(HashTable& heapArg);

void Test_SampleInput(HashTable& hTable){

	int test_cases = 0;
	int sizeOfPair = 0;

	freopen("HashTableSampleInput.txt", "r", stdin);
	cin >> test_cases;

	cout << "TestCases:" << test_cases << endl;

	for (int tc = 0; tc < test_cases; tc++){

		cin >> sizeOfPair;
		cout << "Pair Size:" << sizeOfPair << endl;

		for (int i = 0; i < sizeOfPair; i++){
			std::string name;
			int age;
			cin >> name;
			cin >> age;

			cout << "Name:" << name << endl;
			cout << "Age:" << age << endl;

			hTable.Put(name, age);
		}
	}
	hTable.Print();
}
void Test_RandomisedDataInput(HashTable& heapArg){

}

int main(int argc, char* argv[]){

	HashTable table;
	std::string inputName;

	cout << "Arg Count:" << argc << endl;
	if (argc == 3){

		inputName = argv[2];

		if (strcmp(argv[1], "0") == 0){
			Test_SampleInput(table);
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput(table);
		}
		else {
			Test_SampleInput(table);
		}
	} else {
		Test_SampleInput(table);
	}

	if ( table.Find(inputName)){
		cout << "Age of [" << inputName << "] is [";
		cout << table.Get(inputName) << "]" << endl;
	} else {
		cout << inputName << " not found!" << endl;
	}

	table.Clear();
	return 0;
}
