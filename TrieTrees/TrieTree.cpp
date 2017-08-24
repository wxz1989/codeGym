// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "TrieTree.h"


namespace Tries{

TTPtr TrieTree::pInstance = NULL;
//_TRIE_DIRECTORY_FILE_NAME_

static int charCounter = 0;
TrieTree::TrieTree(){
	mWordCount = 0;
	buildFromDir = false;
	//nodeFactoryPtr = TTNodeFactory::GetInstance();
	pTreeHead = TTNodeFactory::GetInstance()->CreateTrieNode();
	//m_DirHandle = freopen("TrieDirectory.txt", "r+", stdout); ;

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
		if (  pChildPtr ){ pTempHead = pChildPtr; } 
		else { pTempHead = NULL; break; }
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

bool TrieTree::DeleteWord(const std::string& inputString){

	if ( pTreeHead == NULL || inputString.length() == 0 ){ cout << "Delete failed, returning!!!"  <<  endl;return false; }

	cout << "Delete Word Entered" <<  endl;
	bool wordRemoved = false;
	DeleteWordUtil(pTreeHead, inputString, 0, wordRemoved);
	if ( wordRemoved == true ){
		mWordCount--;
	}
	return true;
}

bool TrieTree::DeleteWordUtil(ITrieNodeIntSharedPtr pHead, std::string inputString, int currentIndex, bool& wordRemoved){

	bool retValue = false;
	int tempChar = -1;

	if( pHead == NULL || inputString.length() == 0 ||  (currentIndex < 0)) { return retValue; }
	if (currentIndex  > inputString.length()-1) { return true; }

	tempChar = FindCharIndex (inputString[currentIndex]);

	ITrieNodeIntSharedPtr pChildPtr = pHead->GetChildPtr(tempChar);
	if (  pChildPtr ){ 
		retValue = DeleteWordUtil(pChildPtr, inputString, currentIndex+1, wordRemoved);
		if ( retValue == true ){
			if ( currentIndex == (inputString.length() - 1))  {				//pChildPtr->SetEOW(false);				//pChildPtr->SetEOW(false); ){		//last element of the word 
				if (  pChildPtr->HasChild() == false  ){
					pHead->ResetSharedPtr(tempChar);
					pHead->SetChildPtr(NULL, tempChar);
					if ( pHead->GetChildCount() < 1  ){
						pHead->SetHasChild(false);
					}
					wordRemoved = true;
					return true;
				} else {			
									//Last element of the word being serached but it still has more children
					wordRemoved = true;
					pChildPtr->SetEOW(false);
					return false;
				}
			} else  {
				if ( ! pChildPtr->IsEOW() ){
					if ( pChildPtr->HasChild() == false ){
						pHead->ResetSharedPtr(tempChar);
						pHead->SetChildPtr(NULL, tempChar);
						if ( pHead->GetChildCount() < 1 ){
							pHead->SetHasChild(false);
						}
						return true;
					} 
				}
				return false;
			}
		} 	
	} 
	return retValue;
}

//Trie Tree Implementation
bool	TrieTree::AddWord(const std::string& inputString)
{
	int					iInputStringLength = 0, iIndex=0;
	int tempChar = -1;
	ITrieNodeIntSharedPtr			pTempHead=NULL;

	//if ( FindWord(inputString) ){ cout << inputString << " already Exists!"<< endl; return true; }
	//else { cout << " Not found inserting it again" << endl; }

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

					//if( pTempHead->IsEOW() ){
						pTempHead->SetHasChild(true);
					//}
					pTempHead = pNewNode;
				}
			}
			else{
				pTempHead = pChildPtr;
				if ( iIndex == iInputStringLength -1 ){
					pChildPtr->SetEOW(true);
				}
				
			}
		}
		else {
			cout << "TrieTree is NULL" << endl;
			return false;
		}
	}

	mWordCount++;
	if ( buildFromDir == false ){
		//m_DirHandle.write(inputString);
		AddToDirectory(inputString);
	}
	return true;
}
bool	TrieTree::FindWord(const std::string& inputString)
{
	bool ret = false;
	int					iInputStringLength = 0, iIndex=0;
	int tempChar = 0;
	ITrieNodeIntSharedPtr		pTempHead= NULL;

	if ( pTreeHead == NULL || inputString.length() == 0) {  return false; }

	pTempHead = FindNewHead(inputString);
	if( pTempHead != NULL ){
		cout << "Found" << endl; 
		ret = true;
	} else {
		cout << "Not Found" << endl;
		AddWord(inputString);
		ret = false;
	}

	return ret;
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
		if ( pTempHead == NULL ){ /*cout << "New Head is NULL!" << endl;*/ return -1; }
	} else {
		
		pTempHead = pTreeHead;
		tempChar = FindCharIndex(inputText[0]);

		if( pTempHead->GetChildPtr(tempChar) == NULL ) { return -1; }
		pTempHead = pTempHead->GetChildPtr(tempChar);
	}

	prefix.append(inputText);
	if ( pTempHead->IsEOW()){ cout << prefix << endl; }
	//return ExtractWordFromNode(pTempHead, inputText, prefix);
	return ExtractWordsFromNode(pTempHead, prefix);
}

int TrieTree::ExtractWordsFromNode(ITrieNodeIntSharedPtr pHead, std::string& outputText){

	if ( pHead == NULL ){ return -1; }

	ITrieNodeIntSharedPtr pChildPtr = NULL;

	for ( int iIndex =0; iIndex < Tries::TRIE_MAX_SIZE; iIndex++) {	

		pChildPtr = pHead->GetChildPtr(iIndex);
		if( pChildPtr  == NULL ){ continue;  } 
		outputText += pChildPtr->GetCharValue();
		if( pChildPtr->IsEOW() ){ 
			cout <<outputText << endl; 
		}

		ExtractWordsFromNode(pChildPtr, outputText);
		outputText.erase(outputText.length()-1, 1);
	}
}

int TrieTree::ExtractWordFromNode(ITrieNodeIntSharedPtr pHead, const std::string& prefix, std::string& outputText)
{
	if ( pHead == NULL ){ cout << "Invalid Head Pointer!" << endl; return -1; }

	/*if ( pHead->IsEOW() ){ 
		outputText += pHead->GetCharValue();
		cout << outputText << endl; 
		if ( !pHead->HasChild() ){ return 0;  } 
	}*/
	
//	cout << "Current Head:[" << pHead->GetCharValue()<<"]"; 

	/*for ( int iIndex =0; iIndex < Tries::TRIE_MAX_SIZE; iIndex++){

		ITrieNodeIntSharedPtr pChildPtr = NULL;
		pChildPtr =  pHead->GetChildPtr(iIndex);

		if ( pChildPtr != NULL ){

			if ( pChildPtr->IsEOW() ){

				outputText += pHead->GetCharValue();
				cout << outputText << endl;

				if ( !pChildPtr->HasChild() ){ return 0; }
				else {
					ExtractWordFromNode(pChildPtr, prefix, outputText);
					//outputText.erase(outputText.length()-1, 1);
				}
			} else { 
				//outputText +=  pChildPtr->GetCharValue(); 
				ExtractWordFromNode(pChildPtr, prefix, outputText);
				//outputText.erase(outputText.length()-1, 1);
			}
		}
	}*/

	/*for ( int iIndex =0; iIndex < Tries::TRIE_MAX_SIZE; iIndex++)
	{
		ITrieNodeIntSharedPtr pChildPtr = NULL;
		pChildPtr =  pHead->GetChildPtr(iIndex);

		if( pChildPtr == NULL ){continue;}
		
		if ( pChildPtr->IsEOW() ){

			cout  << "Result EOW:[" <<  outputText << "]" <<  endl;
			outputText += pChildPtr->GetCharValue(); 
			cout  <<"Output:["  << outputText <<  "]" << endl;
			//outputText.erase(outputText.length()-1, 1);
			//cout << " EOW :[" << pChildPtr->HasChild() << "]" << endl;
			if ( !pChildPtr->HasChild() ){ return 0; }
			else{
				ExtractWordFromNode(pChildPtr, prefix, outputText);
				outputText.erase(outputText.length()-1, 1);
				cout  << "Text While Returning EOW:[" << outputText << "]" <<  endl;
			}
		} else { 
			outputText +=  pChildPtr->GetCharValue(); // pHead->pChild[iIndex]->charValue;
			ExtractWordFromNode(pChildPtr, prefix, outputText);
			//cout << "Op Len:[" << outputText.length() << "], Op:[" << outputText << "]" << endl;
			outputText.erase(outputText.length()-1, 1);
			cout  << "Text While Returning No EOW:[" << outputText << "]" <<  endl;
		}
		
	}*/
	return 1;
}

int TrieTree::FindCharIndex(char currentChar){

	int charIndex = -1;
	if ( (int) currentChar >=Tries::TRIE_START_CHAR && (int)currentChar <Tries::TRIE_MAX_SIZE){
		charIndex = currentChar % Tries::TRIE_MAX_SIZE;
	}
	return charIndex;
}

void TrieTree::ListAll(){
	std::string value;
	if( pTreeHead == NULL ){ cout << "Trie tree is empty"<<endl; return;}
	cout << "Words Found in Trie : ["<< mWordCount << "]" << endl;
	ExtractWordsFromNode(pTreeHead, value);
}

void TrieTree::AddToDirectory(const std::string& inputString){
	std::ofstream ofs;
	ofs.open (TrieTree::_TRIE_DIRECTORY_FILE_NAME_, std::ofstream::out | std::ofstream::app);
	cout << "Writing to Trie Directory:[" << TrieTree::_TRIE_DIRECTORY_FILE_NAME_ << "]" << endl;

	if (ofs.is_open()){
		ofs << inputString;
		ofs << endl;
	} else {
		cout << "Error in opening/writing to directory file" << endl;
	}
	ofs.close();
}

bool TrieTree::BuildFromDirectory(void){
	string line;
	ifstream myfile (TrieTree::_TRIE_DIRECTORY_FILE_NAME_);
	if (myfile.is_open()){
		buildFromDir = true;
		while ( getline (myfile,line) ) {
			AddWord(line);
		}
		myfile.close();
	}  else { cout << "Unable to open file" << endl; }

	buildFromDir = false;
	return false;
}
}
