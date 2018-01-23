#include "TrieNode.h"

using namespace std;

namespace Tries {

	TTNFPtr TrieNodeFactory::mInstance= NULL;

	TrieTreeNode::TrieTreeNode(){
		childCount = 0;
		nodeCounter++;
	}

	TrieTreeNode::~TrieTreeNode(){
		nodeCounter--;
	}

	bool TrieTreeNode::HasChild(){
		return bHasChild;
	}
	void TrieTreeNode::SetHasChild(bool hasChild){
		bHasChild = hasChild;
	}
	bool TrieTreeNode::IsEOW(){
		return bEndOfWord;
	}
	void TrieTreeNode::SetEOW(bool eow){
		bEndOfWord = eow;
	}
	char TrieTreeNode::GetCharValue(){
		return charValue;
	}
	void TrieTreeNode::SetCharValue(char value){
		charValue = value;
	}
	void TrieTreeNode::ResetChildren(){
		memset(pChild, '\0', sizeof(char)*TRIE_MAX_SIZE);
	}
	ITrieNodeIntSharedPtr TrieTreeNode::GetChildPtr(int index)	{
		return pChild[index];
	}
	void TrieTreeNode::SetChildPtr(ITrieNodeIntSharedPtr pChildPtr, int index){
		//pChild[index] = pChildPtr;
		//cout << "Child Count++:[" << childCount <<"]" << endl;
		if ( pChildPtr == NULL){
			childCount--;
		} else {
			if ( pChild[index] == NULL ){
				pChild[index].reset();
				pChild[index] = pChildPtr;
				childCount++;
			}
		}
		//cout <<  GetCharValue() <<":[" << childCount <<"]" << endl;
	}

	TrieNodeFactory::TrieNodeFactory(){
	}
	TrieNodeFactory::~TrieNodeFactory(){
		nodeCounter = 0;
	}
	TTNFPtr TrieNodeFactory::GetInstance(){
		if ( mInstance == NULL ){
			mInstance = new TrieNodeFactory();
			atexit(TrieNodeFactory::CleanUp);
		}
		return mInstance;
	}
	void TrieNodeFactory::CleanUp(void){
		delete mInstance;
	}	
	ITrieNodeIntSharedPtr TrieNodeFactory::CreateTrieNode(){
		
#if 0 
		TTNodePtr newNode = new TTNode();
		newNode->SetEOW(false);
		newNode->SetCharValue(Tries::TRIE_EMPTY_CHAR);
		newNode->SetHasChild(false);
		newNode->ResetChildren();
		nodeCounter++;
		return newNode;
#else 
		ITrieNodeIntSharedPtr newSharedPtr = std::make_shared<TTNode>();
		newSharedPtr->SetEOW(false);
		newSharedPtr->SetCharValue(Tries::TRIE_EMPTY_CHAR);
		newSharedPtr->SetHasChild(false);
		newSharedPtr->ResetChildren();
		return newSharedPtr;
	#endif
		
	}
	int TrieNodeFactory::GetNodeCount(void){
		return nodeCounter;
	}

	int TrieTreeNode::GetChildCount(void){
		return childCount;
	}
	void TrieTreeNode::ResetSharedPtr(int index){
		//cout << "Parent:[" << GetCharValue() <<"], Child:["<< pChild[index]->GetCharValue() <<"] Index:[" << index << "]" << endl;
		pChild[index].reset();
	}
}
