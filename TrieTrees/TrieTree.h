#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_INPUT_SIZE 10
#define MAX_ARRAY_SIZE 100
#define MAX_SIZE 26

using namespace std;

struct TrieTreeNode{
	char				charValue;
	TrieTreeNode*		pChild[MAX_SIZE];
	bool				bEndOfWord;
};

typedef TrieTreeNode  TTNode;
typedef TrieTreeNode* TTNodePtr;
typedef TrieTreeNode** TTNodeDPtr;

class TrieTree{

public:
	bool	AddWord(std::string	inputString);
	void	FindWord(std::string inputString);
	int		FindWordByPrefix(std::string inputText);
	bool 	DeleteWord(std::string inputWord);
private:
	TTNodePtr 	CreateTrieTreeNode();
	TTNodePtr 	FindNewHead(std::string);
	int	ExtractWordFromNode(TTNodePtr pHead, std::string, std::string&);
	int	FreeTrieTree(TTNodePtr);
	TrieTree();

public:
	~TrieTree();
	static TrieTree* 	GetInstance();
	static void TrieTerminate();
private:
	static TrieTree* pInstance;
	TTNodePtr pTreeHead;
};


typedef TrieTree* TTPtr;
typedef TrieTree** TTDPtr;



#endif //#ifndef __TRIE_TREE_H__
