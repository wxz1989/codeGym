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
#define MAX_SIZE 26

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve();


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

typedef TrieTreeNode  TTNode;
typedef TrieTreeNode* TTNodePtr;
typedef TrieTreeNode** TTNodeDPtr;


int Initialize();
//Public
bool	InsertValue(TrieTreeNode*	pHead,char*		pInput);
//Public
void	FindWord(TrieTreeNode*	pHead,char*		pInput);

//Public 
int	FindWordByPrefix(TrieTreeNode*	pHead, std::string inputText);

//Should be private and should do cleaup if asked explicitely or whlie terminating the trie object
int	FreeTrieTree(TrieTreeNode*		pHead);

//Private API
int	ExtractWordFromNode(TrieTreeNode*		pHead, std::string, std::string&);

//Go to the word in the middle of the node
TTNodePtr 	FindNewHead(TTNodePtr  pHead);


TTNodePtr 	FindNewHead(TTNodePtr  pHead, std::string inputText){

	char tempChar = '\0';
	if( pHead == NULL ){ return NULL; }
	TTNodePtr pTempHead = pHead;

	for ( int i=0 ; i<inputText.length();i++ ){
		if ( inputText[i] >'A' && inputText[i] <'Z') {				// As of now inputText is considered to be a Single character input
			tempChar = abs('A'- inputText[i] );
		} else {
			tempChar = abs('a'- inputText[i] );
		}
		if ( pTempHead->pChild[tempChar] ){
			pTempHead = pTempHead->pChild[tempChar];
		} else {
			pTempHead = NULL;
			break;
		}
	}
	return ((pTempHead == pHead || pTempHead == NULL) ? NULL : pTempHead);
}

int Initialize(){
	if( __pTrieHead ){
		FreeTrieTree(__pTrieHead);
		__pTrieHead = new TrieTreeNode();

		if ( __pTrieHead == NULL ){ return 0;  }
	}
	return 1;
}

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
	printf("Adding: [%s][%d] ", pInput, iInputStringLength);
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
	if (pHead== NULL || pInput == NULL) {
		cout << "Input String is Incorrect!" << endl;
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
			if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z'){
				tempChar = abs('A'- pInput[iIndex]);
			} else {
				tempChar = abs('a'- pInput[iIndex]);
			}
			if ( pTempHead->pChild[tempChar] )
			{	
				printf("%c",pTempHead->pChild[tempChar]->charValue);
				if( pTempHead->pChild[tempChar]->bEndOfWord ) 
				{
					printf("\nWord Found");
					return;
				}
				pTempHead = pTempHead->pChild[tempChar];
			} else {
				//printf("Not Found");
				return;
			}
		} else {
			printf("\nHead is NULL! TrieTree is NULL");
			return ;
		}
	}
	return ;
}

int	FindWordByPrefix(TrieTreeNode*		pHead,std::string inputText)
{
	char				tempChar='\0';
	int					iIndex=0;
	TrieTreeNode*		pTempHead= NULL;
	std::string prefix;// = inputText;

	if (pHead == NULL || inputText.empty() ) {
		// cout << "Input String is Incorrect!" << endl;
		return -1;
	}

	pTempHead = pHead;

	if ( inputText.length() > 1 ){
		pTempHead = FindNewHead(pHead, inputText);
	} else {
		tempChar = inputText[0];

		if ( tempChar >'A' && tempChar <'Z'){				// As of now inputText is considered to be a Single character input
			tempChar = abs('A'- tempChar);
		} else {
			tempChar = abs('a'- tempChar);
		}
		pTempHead = pTempHead->pChild[tempChar];
	}

	prefix.append(inputText);
	return ExtractWordFromNode(pTempHead, inputText, prefix);
}


int ExtractWordFromNode(TrieTreeNode*	pHead, std::string prefix,std::string& outputText)
{
	if ( pHead == NULL ){
		//cout << "Invalid Head Pointer!" << endl;
		return -1;
	}
	for ( int iIndex =0; iIndex < MAX_SIZE; iIndex++)
	{
		if ( pHead->pChild[iIndex] )
		{
			if ( pHead->pChild[iIndex]->bEndOfWord )
			{
				outputText += pHead->pChild[iIndex]->charValue;
				cout  <<  outputText <<  endl;
				outputText.erase(outputText.length()-1, 1);
					//cout  <<"Removed Last Char: ["<<  outputText << "]" << endl;
				return 0;
			} else { 
					//cout << "Found Character: [" << pHead->pChild[iIndex]->charValue << "]" << endl;
				outputText += pHead->pChild[iIndex]->charValue;
				ExtractWordFromNode(pHead->pChild[iIndex], prefix, outputText);
				outputText.erase(outputText.length()-1, 1);
					//cout  <<"Again Removed Last Char: ["<<  outputText << "]" << endl;
			}
		}
	}
	return 1;
}
int	FreeTrieTree(TrieTreeNode*		pHead)
{
	TrieTreeNode*		pHeadNode = NULL;
	if ( pHead ==NULL ) {
		printf("Trie Head node is NULL! Nothing to Free.");
		return 0;
	}

	if ( pHead->bEndOfWord ){
		//cout << "End of word detected at [" << pHead->charValue << "]" << endl;
		delete pHead;
		return 0;
	}
	pHeadNode = pHead;
	for ( int iIndex = 0; iIndex < MAX_SIZE; iIndex++) {

		if ( pHeadNode->pChild[iIndex]) {
			FreeTrieTree(pHeadNode->pChild[iIndex]);
		}
	}
    delete pHeadNode;
	return 1;
}

void Test_SampleInput(){

	__pTrieHead = new TrieTreeNode();
	//Initialize();
	char A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	std::string inputString;

	freopen("TrieTree_Sample_Input.txt", "r", stdin);

	//Converting String to Number using getline
	
	//cin.ignore(6, '\n');
	//cin.getline(inputString, 50);
	getline(cin, inputString);

	// This code converts from string to number safely.
	stringstream myStream(inputString);
	if ( myStream >> test_cases ){
		cout << "Test cases :[" << test_cases << "]" <<  endl;
	} else {
		cout << "Invalid number, please try again" << endl;
	}

	for (int tc = 0; tc < test_cases; tc++){
		
		//cin.ignore(6 - ((tc+1)*3), '\n');
		//cin.getline(inputString, 50);
		getline(cin , inputString);
		//cout << "Sample Input:[" << inputString << "]" << endl;
		InsertValue(__pTrieHead, (char*)inputString.c_str());
	}

	int Ans = Solve();
	/*std::string searchString;
	while((std::cin>>searchString))  {
		cout << "Read String:[" << searchString << "]" << endl;
	}*/
}
void Test_RandomisedDataInput(){

	//Initialize();
	std::string inputString;
	char A[MAX_ARRAY_SIZE] = { 0 };
	int size = 0;

	//Test cases length
	srand(time(NULL));
	size = rand() % SAMPLE_INPUT_SIZE;

	__pTrieHead = new TrieTreeNode();

	//cout << "Size:[" << size <<"]" << endl;
	for (int i = 0; i< size; i++){

		//Word length
		int wordLength = rand() % MAX_SIZE;

		for ( int j = 0;j < wordLength;j++){
			//Word's Chracters
			int value = rand() % MAX_SIZE;
			A[j] =  'a' + value;
		}
		InsertValue(__pTrieHead, A);
		memset(A, 0, sizeof(char)*wordLength);
	}
	int Ans = Solve();
}


int Solve(){
	std::string searchString("u");
	cout << "************** SEARCH ***************"<< endl ;
	cout << "Search string is: [" << searchString << "]" <<  endl;
	cout << "************** SEARCH RESULTS ***************"<< endl ;
	if ( FindWordByPrefix(__pTrieHead, searchString) == -1 ){
		cout << "No results found" <<  endl;
	}
	cout << "************** SEARCH ENDS ******************"<< endl ;

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
