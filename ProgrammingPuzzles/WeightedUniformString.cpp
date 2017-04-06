#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <map>
#include <vector>
#include <set>

using namespace std;

std::map<char, int> charMap;
std::set<int> charSet;

int MapImpl_Solve(std::string inputString, int* queries, int quetyLength);
bool MapImpl_PrepareSet(std::string inputString);
void MapImpl_PrintSet();
void Test_SampleInput();

void ResetData(){
	charMap.clear();
	charSet.clear();
}

int MapImpl_Solve(std::string inputString, int* queries, int queryLength){
	if ( queryLength <= 0 || inputString.length() == 0 ){ 
		cout << "No" << endl;
		return -1;
	}

	if ( !MapImpl_PrepareSet(inputString) ){ cout << "No" << endl; return -1; } 
	//MapImpl_PrintSet();

	bool found = false;
	int j = 0;

	//cout << "Value:[" <<  value << "]" << endl;
	for (  j = 0; j < queryLength; j++){
		std::set<int>::iterator setIte;
		if ( charSet.find(queries[j]) !=  charSet.end()){
			std::cout<<"Yes"<<endl;
		}else{
			//cout <<  queries[j] << endl;
			std::cout<<"No"<<endl;
		}
	}
	return 0;
}
bool MapImpl_PrepareSet(std::string inputString){

	std::map<char, int>::iterator mapIte;


	//cout << "String:[" << str << "]" << endl;
	for ( int i = 0; i< inputString.length();i++){
		char ch = inputString[i];
		//cout << "Char:["<< ch <<"]" << endl;
		if ( ch >='a' && ch <= 'z'){
			int chIndex = ch - 'a';
			mapIte = charMap.find(ch);

			int value=0;
			if ( mapIte != charMap.end()){
				value = mapIte->second;
				value += 1;
				mapIte->second = value;
				//cout << "Value found:[" << value <<"]" << endl;
			} else {
				value =1;
				//cout << "New Entry:[" << value <<"]" << endl;
				charMap.insert(std::pair<char, int>(ch, value));	
			}
			
			//cout << "Value from Map:"<< value << endl;
			int uniformValue = (chIndex+1)*value;
			//cout << "Char:["<< ch << "], Uniform Value:[" << uniformValue <<"]" << endl;
			//std::cout<<"Values to Insert:[" << uniformValue <<"]" <<  endl;
			charSet.insert(uniformValue);

			//cout << "Char:["<< ch <<"][" << chIndex <<"]" << endl;
		}
	}
	//PrintArray(charCount);
	return true;
}

void MapImpl_PrintSet(){
	std::set<int>::iterator setIte;
	cout << "======================================" << endl;
	for ( setIte = charSet.begin(); setIte != charSet.end();++setIte){
		cout << *setIte << endl;
	}
	cout << "======================================" << endl;
}

void Test_SampleInput(){

	int test_cases = 0;
	int size= 0;

	int* pQueries = NULL;
	char* pInputStr = NULL;

	freopen("WeightedUniformString_SampleInput.txt", "r", stdin);
	cin >> test_cases;

	std::string inputStr;

	for (int tc = 0; tc < test_cases; tc++){

		//cout << "++++++++++++++++++++++++++++++" << endl;
		cin >> inputStr;
		cin >> size;

		pInputStr = new char[inputStr.length()];
		pQueries = new int[size];

		for ( int i = 0 ;i < size ;i++){
			cin >> pQueries[i];
		}	

		memcpy(pInputStr, (char*)inputStr.c_str(), sizeof(char) * inputStr.length());
		int Ans = MapImpl_Solve(pInputStr, pQueries, size);

		delete [] pInputStr;
		delete [] pQueries;
		//cout << "++++++++++++++++++++++++++++++" << endl;
		ResetData();
	}
}

int main(int argc, char* argv[]){
	Test_SampleInput();	
	return 0;
}
