// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <time.h>
#include <stdio_ext.h>

#define SAMPLE_INPUT_SIZE 10
#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve();


#define MAX_SIZE 26
static int __iIndex= 0;

//Implementatio of Trie tree
//data structure for trie

struct TrieTreeNode
{
	int				iIndex;
	char			charValue;
	TrieTreeNode*	pChild[MAX_SIZE];
	bool			bEndOfWord;
};
static TrieTreeNode*	__pTrieHead = NULL;

//Public
bool	InsertValue(TrieTreeNode*	pHead,char*		pInput);
//Public
void	FindWord(TrieTreeNode*	pHead,char*		pInput);

//Public 
void	FindWordByPrefix(TrieTreeNode*	pHead,char*		pInput);
void	FindWordByPrefix(TrieTreeNode*	pHead,std::string inputText);

//Should be private and should do cleaup if asked explicitely or whlie terminating the trie object
void	FreeTrieTree(TrieTreeNode*		pHead);

//Private API
void	ExtractWordFromNode(TrieTreeNode*		pHead, std::string, std::string&);

//Trie Tree Implementation
bool	InsertValue(TrieTreeNode*		pHead, char*		pInput)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TrieTreeNode*		pTempHead= NULL;
	if ( pInput == NULL)
	{
		printf("\nInsertion failed!");
		return false;
	}
	pTempHead = pHead;
	while(pInput[iInputStringLength++]);
	iInputStringLength--;
	printf("InputStr: [%s][%d] ", pInput, iInputStringLength);
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z')
				tempChar = abs('A'- pInput[iIndex]);
			else 
				tempChar = abs('a'- pInput[iIndex]);

			if ( pTempHead->pChild[tempChar]==NULL )
			{	
				//printf("\nNot found!");
				TrieTreeNode*		pTempNode = new TrieTreeNode();			//Make a factory and ask it to generate new nodes., use sample program template to generate new input data 
				if ( pTempNode )
				{
					pTempNode->iIndex= __iIndex;
					__iIndex++;
					pTempNode->charValue = pInput[iIndex];
					if ( iIndex == iInputStringLength-1)
						pTempNode->bEndOfWord = true;
					else
						pTempNode->bEndOfWord = false;

					pTempHead->pChild[tempChar]= pTempNode; 
					pTempHead = pTempNode;
				}
			}
			else
				pTempHead = pTempHead->pChild[tempChar];
		}
		else
		{
			printf("\nHead is NULL! TrieTree is NULL");
			return false;
		}
	}
	cout << endl;
	return true;
}
void	FindWord(TrieTreeNode*		pHead, char*		pInput)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TrieTreeNode*		pTempHead= NULL;
	if (pHead== NULL || pInput == NULL)
	{
		printf("\nInput String is Incorrect!");
		return ;
	}

	pTempHead = pHead;
	while(pInput[iInputStringLength++]);
	iInputStringLength--;

	printf("\nInput String Length is : [%d]",iInputStringLength);
	printf("\nWord Searching...");
	printf("\n");
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z')
				tempChar = abs('A'- pInput[iIndex]);
			else 
				tempChar = abs('a'- pInput[iIndex]);
			if ( pTempHead->pChild[tempChar] )
			{	
				printf("%c",pTempHead->pChild[tempChar]->charValue);
				if( pTempHead->pChild[tempChar]->bEndOfWord ) 
				{
					printf("\nWord Found");
					return;
				}
				pTempHead = pTempHead->pChild[tempChar];
			}
			else{
				//printf("Not Found");
				return;
			}
		}
		else
		{
			printf("\nHead is NULL! TrieTree is NULL");
			return ;
		}
	}
	return ;
}
void	FindWordByPrefix(TrieTreeNode*		pHead,std::string inputText)
{
	char				tempChar='\0';
	int					iIndex=0;
	TrieTreeNode*		pTempHead= NULL;

	if (pHead== NULL || inputText.empty() ) {
		cout << "Input String is Incorrect!" << endl;
		return ;
	}

	pTempHead = pHead;

	if ( inputText.length() > 1 ){
		cout << "First find all character matching the inputText, then find all it's comnbinations!" << endl;
		//Do Something!
	} else {
		cout << "Character to match is: [" << inputText <<"]["<< inputText[0] <<"]"<< endl;
	}
	cout <<"Index:"  << inputText[0] << endl;
	tempChar = inputText[0];

	if ( inputText[0] >'A' && inputText[0] <'Z')				// As of now inputText is considered to be a Single character input
		tempChar = abs('A'- tempChar);
	else 
		tempChar = abs('a'- tempChar);

	if ( pTempHead->pChild[tempChar] ){	
		std::string prefix;
		//prefix += ('a' + tempChar);
		prefix.append(inputText);
		ExtractWordFromNode(pTempHead->pChild[tempChar], inputText, prefix);
	}
	else
	{
		printf("\nHead is NULL! TrieTree is NULL");
		return ;
	}
	printf("\n");
	return ;
}


void ExtractWordFromNode(TrieTreeNode*	pHead, std::string prefix,std::string& outputText)
{
	if ( pHead )
	{
		for ( int iIndex =0; iIndex < MAX_SIZE; iIndex++)
		{
			if ( pHead->pChild[iIndex] )
			{
				if ( pHead->pChild[iIndex]->bEndOfWord )
				{
					outputText += pHead->pChild[iIndex]->charValue;
					cout  <<"Found Word: ["<<  outputText << "]" << endl;
					outputText.erase(outputText.length()-1, 1);
					//cout  <<"Removed Last Char: ["<<  outputText << "]" << endl;
					return;
				} else { 
					//cout << "Found Character: [" << pHead->pChild[iIndex]->charValue << "]" << endl;
					outputText += pHead->pChild[iIndex]->charValue;
					ExtractWordFromNode(pHead->pChild[iIndex], prefix, outputText);
					outputText.erase(outputText.length()-1, 1);
					//cout  <<"Again Removed Last Char: ["<<  outputText << "]" << endl;
				}
			}
		}
	}
}
void	FreeTrieTree(TrieTreeNode*		pHead)
{
	TrieTreeNode*		pHeadNode = NULL;
	if ( pHead ==NULL ) {
		printf("Trie Head node is NULL! Nothing to Free.");
		return;
	}

	if ( pHead->bEndOfWord ){
		//cout << "End of word detected at [" << pHead->charValue << "]" << endl;
		delete pHead;
		return;
	}
	pHeadNode = pHead;
	for ( int iIndex = 0; iIndex < MAX_SIZE; iIndex++) {

		if ( pHeadNode->pChild[iIndex]) {
			//cout << "Will Delete :[" << pHeadNode->pChild[iIndex]->charValue << "] " << endl;
			FreeTrieTree(pHeadNode->pChild[iIndex]);
			//cout << "Deleting : ["<< iIndex <<"] Char Value[" << pHeadNode->pChild[iIndex]->charValue << "] " << endl;

			//delete pHeadNode->pChild[iIndex];
			//pHeadNode->pChild[iIndex] = NULL;
			//cout << "returning!!!" << endl;
			//return;
		}
	}
	//cout << "Deleting headNode: [" << pHeadNode->charValue << "] " << endl;
    delete pHeadNode;
	return;
}

void Test_SampleInput(){

	__pTrieHead = new TrieTreeNode();
	char A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	std::string inputString;

	fflush(stdin);
	freopen("TrieTree_Sample_Input.txt", "r", stdin);
	cin.clear();        //clear badbit flag
    cin.sync();   
	//Converting String to Number using getline
	getline(cin, inputString);

	// This code converts from string to number safely.
	stringstream myStream(inputString);
	if ( myStream >> test_cases ){
		cout << "Test cases [:" << test_cases << "]" <<  endl;
	} else {
		cout << "Invalid number, please try again" << endl;
	}
	
	fflush(stdin);
	for (int tc = 0; tc < test_cases; tc++){
		cin.clear();        //clear badbit flag
    	cin.sync();   
		getline(cin , inputString);;
		//cout << "Sample Input:[" << inputString << "]" << endl;
		InsertValue(__pTrieHead, (char*)inputString.c_str());
		
	}
	fflush(stdin);
	fclose(stdin);

	int Ans = Solve();
	inputString.clear();

	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	__fpurge(stdin);
	  
	cin >> inputString;
	if( cin.fail() ){
		cout << "CIN failed" << endl;
		cin.clear();        //clear badbit flag
    	cin.sync(); 
	} else {
		cout << "CIN worked" << endl;
	}

	int i= 0;
	cin >> i;
	cout << i << endl;

	cout <<"Test:" << inputString << endl;
}
void Test_RandomisedDataInput(){

	char A[MAX_ARRAY_SIZE] = { 0 };
	int size = 0;

	srand(time(NULL));
	size = rand() % SAMPLE_INPUT_SIZE;
	srand(time(NULL));

	for (int i = 0; i< size; i++){
		int value = rand() % MAX_SIZE;
		A[i] = value;
	}

}

void SearchWordByPrefixInLoop(){

	/*while(1){

		std::string searchString;
		cin.clear();        //clear badbit flag
    	cin.sync();   
		//getline(cin, searchString);
		
		char ch = getchar();
		if ( ch == 'q' || ch == 'Q'){
			return;
		} else {
			cin >> searchString;
			cout << "Search Input String is:" << searchString << endl;
			FindWordByPrefix(__pTrieHead, searchString);
		}
	}*/

	return;
}


int Solve(){
	//This is fixed at first so, you know the fixed characters and iterate untill you reach EOW.
	//SearchWordByPrefixInLoop();
	FreeTrieTree(__pTrieHead);
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
