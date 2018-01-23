#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

// TrieTree.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>

#include "TrieNode.h"

namespace Tries{

using namespace std;

class TrieTree;

typedef TrieTree* TTPtr;
typedef TrieTree** TTDPtr;

typedef std::shared_ptr<TrieTree> TTSharedPtr;


class TrieTree{

	//Hash Computation
	
	static const unsigned int MOD_PRIME = 2069;
	static const int HASH_TABLE_SIZE = 300;
	int hashElementCount;
	int CollisionArray[MOD_PRIME];
	//Hash Table


	long mWordCount;
	const std::string _TRIE_DIRECTORY_FILE_NAME_ = ".trie_words_directory.txt";
	const std::string _ENGLISH_DICTIONARY_ = ".englishdictionary.txt";
public:
	bool	AddWord(const std::string& inputString);
	bool	FindWord(const std::string& inputString);
	void	ListAll(void);
	int		FindWordByPrefix(const std::string& inputText);
	bool 	DeleteWord(const std::string& inputWord);
	bool 	BuildFromDirectory(void);
	bool 	BuildFromEnglishDirectory(void);
	void 	ShowCollisionArray();
private:
	bool 	DeleteWordUtil(ITrieNodeIntSharedPtr pHead, std::string inputText, int currentIndex, bool& wordRemoved);
	void AddToDirectory(const std::string&);
	int FindCharIndex(char currentChar);
	/*TTNodePtr*/ ITrieNodeIntSharedPtr FindNewHead(const std::string&);
	int	ExtractWordFromNode(/*TTNodePtr*/ITrieNodeIntSharedPtr pHead, const std::string&, std::string&);
	int ExtractWordsFromNode(ITrieNodeIntSharedPtr pHead, std::string& outputText);
	int Hash(const std::string& source);
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
	bool buildFromDir;
	//File* m_DirHandle;
	static TTPtr pInstance;
	/*TTNodePtr*/ ITrieNodeIntSharedPtr pTreeHead;
	//TTNFPtr	nodeFactoryPtr;			//No Specific need of keeping this as member
};

}


#endif //#ifndef __TRIE_TREE_H__
