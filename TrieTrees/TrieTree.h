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

class TrieTree{

public:
	bool	AddWord(const std::string& inputString);
	void	FindWord(const std::string& inputString);
	int		FindWordByPrefix(const std::string& inputText);
	bool 	DeleteWord(const std::string& inputWord);
private:

	int FindCharIndex(char currentChar);
	TTNodePtr 	TrieNodeFactory();
	TTNodePtr 	FindNewHead(const std::string&);
	int	ExtractWordFromNode(TTNodePtr pHead, const std::string&, std::string&);
	int	FreeTrieTree(TTNodePtr);

	//Private Constructor
	TrieTree();

public:
	//Public Destructor
	~TrieTree();
	static TTPtr 	GetInstance();
	static void TrieTerminate();
private:
	static TTPtr pInstance;
	TTNodePtr pTreeHead;
	//TTNFPtr	nodeFactoryPtr;			//No Specific need of keeping this as member
};

}


#endif //#ifndef __TRIE_TREE_H__
