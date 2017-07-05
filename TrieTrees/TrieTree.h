#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "TrieNode.h"

namespace Tries{

using namespace std;

class TrieTree;

typedef TrieTree* TTPtr;
typedef TrieTree** TTDPtr;

typedef std::shared_ptr<TrieTree> TTSharedPtr;

class TrieTree{

public:
	bool	AddWord(const std::string& inputString);
	void	FindWord(const std::string& inputString);
	int		FindWordByPrefix(const std::string& inputText);
	bool 	DeleteWord(const std::string& inputWord);
private:

	int FindCharIndex(char currentChar);
	/*TTNodePtr*/ ITrieNodeIntSharedPtr FindNewHead(const std::string&);
	int	ExtractWordFromNode(/*TTNodePtr*/ITrieNodeIntSharedPtr pHead, const std::string&, std::string&);
#if 0 
	TTNodePtr 	TrieNodeFactory();
	int	FreeTrieTree(TTNodePtr);
#endif
	//Private Constructor
	TrieTree();

public:
	//Public Destructor
	~TrieTree();
	static TTPtr 	GetInstance();
	static void TrieTerminate();
private:
	static TTPtr pInstance;
	/*TTNodePtr*/ ITrieNodeIntSharedPtr pTreeHead;
	//TTNFPtr	nodeFactoryPtr;			//No Specific need of keeping this as member
};

}


#endif //#ifndef __TRIE_TREE_H__
