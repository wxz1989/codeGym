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
	bool 				bHasChild;
	bool				bEndOfWord;
	char				charValue;
	TrieTreeNode*		pChild[MAX_SIZE];
};

typedef TrieTreeNode  TTNode;
typedef TrieTreeNode* TTNodePtr;
typedef TrieTreeNode** TTNodeDPtr;

class TrieTree{

public:
	bool	AddWord(const std::string& inputString);
	void	FindWord(const std::string& inputString);
	int		FindWordByPrefix(const std::string& inputText);
	bool 	DeleteWord(const std::string& inputWord);
private:
	TTNodePtr 	TrieNodeFactory();
	TTNodePtr 	FindNewHead(const std::string&);
	int	ExtractWordFromNode(TTNodePtr pHead, const std::string&, std::string&);
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
