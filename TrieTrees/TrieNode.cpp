#include "TrieNode.h"

using namespace std;

namespace Tries {

	TTNFPtr TrieNodeFactory::mInstance= NULL;

	TrieTreeNode::TrieTreeNode(){
	}

	TrieTreeNode::~TrieTreeNode(){

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
	ITrieNodeInterfacePtr TrieTreeNode::GetChildPtr(int index)	{
		return pChild[index];
	}
	void TrieTreeNode::SetChildPtr(ITrieNodeInterfacePtr pChildPtr, int index){
		pChild[index] = pChildPtr;
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
	TTNodePtr TrieNodeFactory::CreateTrieNode(){
		TTNodePtr newNode = new TTNode();

		newNode->SetEOW(false);
		newNode->SetCharValue(Tries::TRIE_EMPTY_CHAR);
		newNode->SetHasChild(false);
		newNode->ResetChildren();

		nodeCounter++;

		return newNode;
	}
	int TrieNodeFactory::GetNodeCount(void){
		return nodeCounter;
	}
}
