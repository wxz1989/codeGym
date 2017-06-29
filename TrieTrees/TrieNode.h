#ifndef __TRIE_NODE_H__
#define __TRIE_NODE_H__

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

namespace Tries{

	static const char TRIE_EMPTY_CHAR='\0';
	static const int  TRIE_MAX_SIZE=128; //26	//All character set representable by ASCII character set	
	static const int  TRIE_START_CHAR=32; 			//Beginning of the meaning full charactes 

	class ITrieTreeNode;
	class TrieTreeNode;
	class TrieNodeFactory;

	typedef ITrieTreeNode ITrieNodeInterface;
	typedef ITrieTreeNode* ITrieNodeInterfacePtr;
	typedef ITrieTreeNode** ITrieNodeInterfaceDPtr;

	typedef TrieTreeNode  	TTNode;
	typedef ITrieTreeNode* 	TTNodePtr;
	typedef ITrieTreeNode** TTNodeDPtr;

	typedef TrieNodeFactory   TTNodeFactory;
	typedef TrieNodeFactory*  TTNFPtr;
	typedef TrieNodeFactory** TTNFDPtr;

	class ITrieTreeNode{
	protected:
		bool	bHasChild;
		bool	bEndOfWord;
		char	charValue;
		ITrieNodeInterfacePtr	pChild[TRIE_MAX_SIZE];
	public:
		/*ITrieTreeNode();
		virtual ~ITrieTreeNode();*/
		virtual bool HasChild() = 0;
		virtual void SetHasChild(bool hasChild) = 0;
		virtual bool IsEOW() = 0;
		virtual void SetEOW(bool eow) = 0;
		virtual char GetCharValue() = 0;
		virtual void SetCharValue(char value) = 0;
		virtual void ResetChildren() = 0;
		virtual ITrieNodeInterfacePtr GetChildPtr(int index) = 0;
		virtual void SetChildPtr(ITrieNodeInterfacePtr pChildPtr, int index) = 0;
	};

	class TrieTreeNode : public ITrieTreeNode{
	public:
		TrieTreeNode();
		virtual ~TrieTreeNode();
	public:

		bool HasChild();
		void SetHasChild(bool hasChild);
		bool IsEOW();
		void SetEOW(bool eow);
		char GetCharValue();
		void SetCharValue(char value);
		void ResetChildren();
		ITrieNodeInterfacePtr  GetChildPtr(int index);
		void SetChildPtr(ITrieNodeInterfacePtr pChildPtr, int index);
	};

	class TrieNodeFactory{
	public:
		static TTNFPtr mInstance;
	private:
		int nodeCounter;
		TrieNodeFactory();
	public:
		~TrieNodeFactory();
		static TTNFPtr GetInstance();
		static void CleanUp(void);
		TTNodePtr CreateTrieNode();
		int GetNodeCount(void);
	};

}
#endif //#ifndef __TRIE_NODE_H__
