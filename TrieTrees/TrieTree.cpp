// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "TrieTree.h"

TTPtr TrieTree::pInstance = NULL;

TrieTree::TrieTree(){
	pTreeHead = CreateTrieTreeNode();
}

TrieTree::~TrieTree(){
	cout << "Destructor++" << endl;
	FreeTrieTree(pTreeHead);
	pTreeHead = NULL;
	cout << "Destructor--" << endl;
}	

TTNodePtr 	TrieTree::FindNewHead(std::string inputText){

	char tempChar = '\0';
	if( pInstance == NULL || pTreeHead == NULL ){ return NULL; }
	TTNodePtr pTempHead = pTreeHead;

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
	return ((pTempHead == pTreeHead || pTempHead == NULL) ? NULL : pTempHead);
}

TrieTree* TrieTree::GetInstance(){
	if( !pInstance ){
		pInstance = new TrieTree();
		if ( pInstance == NULL ){ return NULL;  }

		int retValue = atexit(TrieTree::TrieTerminate);
	}
	return pInstance;
}

void TrieTree::TrieTerminate(){
	cout << "TrieTerminate++" << endl;
	if ( pInstance ){
		delete pInstance;
		pInstance= NULL;
	}
	cout << "TrieTerminate--" << endl;
}

bool TrieTree::DeleteWord(std::string inputWord){
	return false;
}

//Trie Tree Implementation
bool	TrieTree::AddWord(std::string	inputString)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TTNodePtr			pTempHead= NULL;

	iInputStringLength  = inputString.length();

	if ( iInputStringLength == 0 ){ return false; }

	if ( pInstance == NULL || pTreeHead == NULL ) {
		cout << " Insertion failed!" << endl;
		return false;
	}
	pTempHead = pTreeHead;
	//while(pInput[iInputStringLength++]);
	
	cout<<"Adding: [" << inputString << "], Length:["   << iInputStringLength << "]" << endl;
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( inputString[iIndex] >'A' && inputString[iIndex]<'Z')
				tempChar = abs('A'- inputString[iIndex]);
			else 
				tempChar = abs('a'- inputString[iIndex]);

			if ( pTempHead->pChild[tempChar]==NULL )
			{	
				TTNodePtr pTempNode = CreateTrieTreeNode();			//Make a factory and ask it to generate new nodes., use sample program template to generate new input data 
				if ( pTempNode )
				{
					pTempNode->charValue = inputString[iIndex];
					if ( iIndex == iInputStringLength-1)
						pTempNode->bEndOfWord = true;
					else
						pTempNode->bEndOfWord = false;

					pTempHead->pChild[tempChar]= pTempNode; 
					/*
						The currently where a new child has been added, 
						would be the end of the world for earlier added word, 
						but when new matching word is added, 
						it still would be an end of the world but should be marked fas has child 
						so that it won't be deleted while freeing trie.
					*/

					if( pTempHead->bEndOfWord ){
						pTempHead->bHasChild =true ;
					}
					pTempHead = pTempNode;
				}
			}
			else{
				pTempHead = pTempHead->pChild[tempChar];
			}
		}
		else {
			cout << "TrieTree is NULL" << endl;
			return false;
		}
	}
	return true;
}
void	TrieTree::FindWord( std::string inputString)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TTNodePtr		pTempHead= NULL;
	
	if ( pTreeHead == NULL || pTreeHead == NULL) {
		cout << "Input String is Incorrect!" << endl;
		return ;
	}

	pTempHead = pTreeHead;
	iInputStringLength  = inputString.length();

	if ( iInputStringLength == 0 ){ return ; }

	cout<<"Input String Length is:" << iInputStringLength << endl;
	cout << "Word Searching..."<< endl;

	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( inputString[iIndex] >'A' && inputString[iIndex]<'Z'){
				tempChar = abs('A'- inputString[iIndex]);
			} else {
				tempChar = abs('a'- inputString[iIndex]);
			}
			if ( pTempHead->pChild[tempChar] )
			{	
				cout<<"CharValue:[" << pTempHead->pChild[tempChar]->charValue << "]" <<  endl;
				if( pTempHead->pChild[tempChar]->bEndOfWord ) 
				{
					cout<<"Word Found"<< endl;
					return;
				}
				pTempHead = pTempHead->pChild[tempChar];
			} else {
				return;
			}
		} else {
			cout << "Head is NULL!" << endl;
			return ;
		}
	}
	return ;
}

int	TrieTree::FindWordByPrefix(std::string inputText)
{
	char				tempChar='\0';
	int					iIndex=0;
	TTNodePtr		pTempHead= NULL;
	std::string prefix;// = inputText;

	if (pTreeHead == NULL || inputText.empty() ) {
		// cout << "Input String is Incorrect!" << endl;
		return -1;
	}

	//pTempHead = pTreeHead;

	if ( inputText.length() > 1 ){
		pTempHead = FindNewHead(inputText); 
		if ( pTempHead == NULL ){ cout << "New Head is NULL" << endl; return -1; }
	} else {
		pTempHead = pTreeHead;
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


int TrieTree::ExtractWordFromNode(TTNodePtr pHead, std::string prefix,std::string& outputText)
{
	if ( pHead == NULL ){ cout << "Invalid Head Pointer!" << endl; return -1;
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
				//	cout << "Found Character: [" << pHead->pChild[iIndex]->charValue << "]" << endl;
				outputText += pHead->pChild[iIndex]->charValue;
				ExtractWordFromNode(pHead->pChild[iIndex], prefix, outputText);
				outputText.erase(outputText.length()-1, 1);
					//cout  <<"Again Removed Last Char: ["<<  outputText << "]" << endl;
			}
		}
	}
	return 1;
}
int	TrieTree::FreeTrieTree(TTNodePtr pHeadNode)
{
	if ( pInstance ==NULL || pHeadNode == NULL ) {
		cout << "Trie Head node is NULL! Nothing to Free." << endl;
		return 0;
	}

	if ( pHeadNode->bEndOfWord && pHeadNode->bHasChild==false ){
		//cout << "End of word detected at [" << pHead->charValue << "]" << endl;
		delete pHeadNode;
		return 0;
	}
	for ( int iIndex = 0; iIndex < MAX_SIZE; iIndex++) {

		if ( pHeadNode->pChild[iIndex]) {
			FreeTrieTree(pHeadNode->pChild[iIndex]);		
		}
	}
    delete pHeadNode;
	return 1;
}


TTNodePtr TrieTree::CreateTrieTreeNode(){
	TTNodePtr pNewNode = NULL;
	pNewNode = new TrieTreeNode();

	pNewNode->charValue ='\0';
	pNewNode->bEndOfWord = false;
	pNewNode->bHasChild = false;
	memset(pNewNode->pChild, 0, sizeof(char)*MAX_SIZE);

	return pNewNode;
}
