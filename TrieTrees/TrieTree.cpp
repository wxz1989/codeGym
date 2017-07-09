// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "TrieTree.h"


namespace Tries{

TTPtr TrieTree::pInstance = NULL;

static int charCounter = 0;
TrieTree::TrieTree(){

	//nodeFactoryPtr = TTNodeFactory::GetInstance();
	pTreeHead = TTNodeFactory::GetInstance()->CreateTrieNode();

}

TrieTree::~TrieTree(){
	cout << "Destructor++" << endl;
	//FreeTrieTree(pTreeHead);
	pTreeHead = NULL;
	cout << "Current Character Counter:[" << TTNodeFactory::GetInstance()->GetNodeCount() <<"]" << endl;
	cout << "Destructor--" << endl;
}	

ITrieNodeIntSharedPtr 	TrieTree::FindNewHead(const std::string& inputText){

	int tempChar = -1;
	if( pInstance == NULL || pTreeHead == NULL ){ return NULL; }
	ITrieNodeIntSharedPtr pTempHead = pTreeHead;

	for ( int i=0 ; i<inputText.length();i++ ){
		tempChar = FindCharIndex (inputText[i]);

		ITrieNodeIntSharedPtr pChildPtr = pTempHead->GetChildPtr(tempChar);
		if (  pChildPtr ){
			pTempHead = pChildPtr;
		} else {
			pTempHead = NULL;
			break;
		}
	}
	return ((pTempHead == pTreeHead || pTempHead == NULL) ? NULL : pTempHead);
}

TTPtr TrieTree::GetInstance(){
	if( !pInstance ){
		pInstance = new TrieTree();
		if ( pInstance == NULL ){ return NULL;  }

		int retValue = atexit(TrieTree::TrieTerminate);
	}
	return pInstance;
}

void TrieTree::TrieTerminate(){
	cout << "Current Character Counter:[" << TTNodeFactory::GetInstance()->GetNodeCount() <<"]" << endl;
	cout << "TrieTerminate++" << endl;
	if ( pInstance ){
		delete pInstance;
		pInstance= NULL;
	}
	cout << "TrieTerminate--" << endl;
}

bool TrieTree::DeleteWord(const std::string& inputWord){
	return false;
}

//Trie Tree Implementation
bool	TrieTree::AddWord(const std::string& inputString)
{
	int					iInputStringLength = 0, iIndex=0;
	int tempChar = -1;
	ITrieNodeIntSharedPtr			pTempHead=NULL;

	iInputStringLength  = inputString.length();

	if ( iInputStringLength == 0 ){ return false; }

	if ( pInstance == NULL || pTreeHead == NULL ) {
		cout << " Insertion failed!" << endl;
		return false;
	}
	pTempHead = pTreeHead;
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			tempChar = FindCharIndex (inputString[iIndex]);

			ITrieNodeIntSharedPtr pChildPtr = pTempHead->GetChildPtr(tempChar);

			if ( pChildPtr == NULL )
			{	
				ITrieNodeIntSharedPtr pNewNode = TTNodeFactory::GetInstance()->CreateTrieNode();//nodeFactoryPtr->CreateTrieNode(); //TrieNodeFactory();			//Make a factory and ask it to generate new nodes., use sample program template to generate new input data 
				charCounter = TTNodeFactory::GetInstance()->GetNodeCount();
				
				if ( pNewNode )
				{
					pNewNode->SetCharValue(inputString[iIndex]);
					if ( iIndex == iInputStringLength-1)
						pNewNode->SetEOW(true);
					else
						pNewNode->SetEOW(false);

					pTempHead->SetChildPtr(pNewNode, tempChar);

					if( pTempHead->IsEOW() ){
						pTempHead->SetHasChild(true);
					}
					pTempHead = pNewNode;
				}
			}
			else{
				pTempHead = pChildPtr;
			}
		}
		else {
			cout << "TrieTree is NULL" << endl;
			return false;
		}
	}
	return true;
}
void	TrieTree::FindWord(const std::string& inputString)
{
	int					iInputStringLength = 0, iIndex=0;
	int tempChar = 0;
	ITrieNodeIntSharedPtr		pTempHead= NULL;

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
			tempChar =  FindCharIndex(inputString[iIndex]);

			ITrieNodeIntSharedPtr pChildPtr = pTempHead->GetChildPtr(tempChar);

			if ( pChildPtr )
			{	
				cout<<"CharValue:[" << pChildPtr->GetCharValue() << "]" <<  endl;
				if( pChildPtr->IsEOW() ) 
				{
					cout<<"Word Found"<< endl;
					return;
				}
				pTempHead = pChildPtr;
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

/*
	This functiuon should check for both upper and lower test case character
	If input character is any character from alphabest character range. (65-90 OR 97-122)
*/


int	TrieTree::FindWordByPrefix(const std::string& inputText)
{
	int tempChar = -1;
	int					iIndex=0;
	ITrieNodeIntSharedPtr		pTempHead= NULL;
	std::string prefix;// = inputText;

	if (pTreeHead == NULL || inputText.empty() ) { return -1; }

	if ( inputText.length() > 1 ){
		pTempHead = FindNewHead(inputText); 
		if ( pTempHead == NULL ){ cout << "New Head is NULL!" << endl; return -1; }
	} else {
		pTempHead = pTreeHead;
		tempChar = FindCharIndex(inputText[0]);

		//If inputText is of only One character and it matches with already inserted word(Single char) then print that first
		if ( inputText.length() ==1 && pTempHead->GetChildPtr(tempChar)->GetCharValue() == inputText[0]){
			cout << inputText <<  endl;
		}
		pTempHead = pTempHead->GetChildPtr(tempChar);
	}

	prefix.append(inputText);
	return ExtractWordFromNode(pTempHead, inputText, prefix);
}


int TrieTree::ExtractWordFromNode(ITrieNodeIntSharedPtr pHead, const std::string& prefix, std::string& outputText)
{
	if ( pHead == NULL ){ cout << "Invalid Head Pointer!" << endl; return -1; }
	
	for ( int iIndex =0; iIndex < Tries::TRIE_MAX_SIZE; iIndex++)
	{
		ITrieNodeIntSharedPtr pChildPtr = NULL;
		pChildPtr =  pHead->GetChildPtr(iIndex);
		if ( pChildPtr != NULL ){
			if ( pChildPtr->IsEOW() ){

				outputText += pChildPtr->GetCharValue(); 
				cout  <<  outputText <<  endl;
				//outputText.erase(outputText.length()-1, 1);
				//cout << " EOW :[" << pChildPtr->HasChild() << "]" << endl;
				if ( !pChildPtr->HasChild() ){
					return 0;
				}
				else{
					ExtractWordFromNode(pChildPtr, prefix, outputText);
					outputText.erase(outputText.length()-1, 1);
				}
			} else { 
				outputText +=  pChildPtr->GetCharValue(); // pHead->pChild[iIndex]->charValue;
				ExtractWordFromNode(pChildPtr, prefix, outputText);
				//cout << "Op Len:[" << outputText.length() << "], Op:[" << outputText << "]" << endl;
				outputText.erase(outputText.length()-1, 1);
			}
		}
	}
	return 1;
}

//Usage of Shared pointer make use of this API obsolete..
#if 0 
int	TrieTree::FreeTrieTree(TTNodePtr pHeadNode)
{
	if ( pInstance ==NULL || pHeadNode == NULL ) {
		cout << "Trie Head node is NULL! Nothing to Free." << endl;
		return 0;
	}

	if ( pHeadNode->IsEOW() && pHeadNode->HasChild() ==false ){
		delete pHeadNode;
		charCounter--;
		return 0;
	}
	for ( int iIndex = 0; iIndex < Tries::TRIE_MAX_SIZE; iIndex++) {

		TTNodePtr pChildPtr = pHeadNode->GetChildPtr(iIndex);
		if ( pChildPtr ) {
			FreeTrieTree(pChildPtr);		
		}
	}
    delete pHeadNode;
    charCounter--;
	return 1;
}
#endif

/*
1. Node Creation is move the a differnet class which has it's concrete and abstract implementaion
2. So this API shold not be used anymore

TTNodePtr TrieTree::TrieNodeFactory(){

	TTNodePtr pNewNode = NULL;
	pNewNode = new TrieTreeNode();

	if ( pNewNode == NULL ){ return NULL; }

	pNewNode->SetCharValue(EMPTY_CHAR);
	pNewNode->SetEOW(false);
	pNewNode->SetHasChild(false);
	pNewNode->ResetChildren();

	charCounter++;
	return pNewNode;
}*/

int TrieTree::FindCharIndex(char currentChar){

	int charIndex = -1;
	if ( (int) currentChar >=Tries::TRIE_START_CHAR && (int)currentChar <Tries::TRIE_MAX_SIZE){
		charIndex = currentChar % Tries::TRIE_MAX_SIZE;
	}
	return charIndex;
}

}
