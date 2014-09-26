// TrieTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <stdio.h>

#define MAX_SIZE 26
static int __iIndex= 0;

//Implementatio of Trie tree
//data structure for trie

struct TrieTreeNode
{
	int				iIndex;
	char			charValue;
	TrieTreeNode*	pChild[MAX_SIZE];
	bool			bEndOfWord;
};
static TrieTreeNode*	__pTrieHead = NULL;

bool	InsertValue(TrieTreeNode*	pHead,char*		pInput);
void	FindWord(TrieTreeNode*	pHead,char*		pInput);
void	FindWordByPrefix(TrieTreeNode*	pHead,char*		pInput);
void	FreeTrieTree(TrieTreeNode*		pHead);
void	ExtractWordFromNode(TrieTreeNode*		pHead);

//Trie Tree Implementation
bool	InsertValue(TrieTreeNode*		pHead, char*		pInput)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TrieTreeNode*		pTempHead= NULL;
	if ( pInput == NULL)
	{
		printf("\nInsertion failed!");
		return false;
	}
	pTempHead = pHead;
	while(pInput[iInputStringLength++]);
	iInputStringLength--;
	printf("\nInput String Length is : [%d]",iInputStringLength);
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z')
				tempChar = abs('A'- pInput[iIndex]);
			else 
				tempChar = abs('a'- pInput[iIndex]);

			if ( pTempHead->pChild[tempChar]==NULL )
			{	
				printf("\nNot found!");
				TrieTreeNode*		pTempNode = new TrieTreeNode();
				if ( pTempNode )
				{
					pTempNode->iIndex= __iIndex;
					__iIndex++;
					pTempNode->charValue = pInput[iIndex];
					if ( iIndex == iInputStringLength-1)
						pTempNode->bEndOfWord = true;
					else
						pTempNode->bEndOfWord = false;

					pTempHead->pChild[tempChar]= pTempNode; 
					pTempHead = pTempNode;
				}
			}
			else
				pTempHead = pTempHead->pChild[tempChar];
		}
		else
		{
			printf("\nHead is NULL! TrieTree is NULL");
			return false;
		}
	}
	return true;
}
void	FindWord(TrieTreeNode*		pHead, char*		pInput)
{
	int					iInputStringLength = 0, iIndex=0;
	char				tempChar='\0';
	TrieTreeNode*		pTempHead= NULL;
	if (pHead== NULL || pInput == NULL)
	{
		printf("\nInput String is Incorrect!");
		return ;
	}

	pTempHead = pHead;
	while(pInput[iInputStringLength++]);
	iInputStringLength--;

	printf("\nInput String Length is : [%d]",iInputStringLength);
	printf("\nWord Searching...");
	printf("\n");
	for ( iIndex = 0; iIndex < iInputStringLength; iIndex++)
	{
		if ( pTempHead )
		{
			if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z')
				tempChar = abs('A'- pInput[iIndex]);
			else 
				tempChar = abs('a'- pInput[iIndex]);
			if ( pTempHead->pChild[tempChar] )
			{	
				printf("%c",pTempHead->pChild[tempChar]->charValue);
				if( pTempHead->pChild[tempChar]->bEndOfWord ) 
				{
					printf("\nWord Found");
					return;
				}
				pTempHead = pTempHead->pChild[tempChar];
			}
			else
			{
				printf("Not Found");
				return;
			}
		}
		else
		{
			printf("\nHead is NULL! TrieTree is NULL");
			return ;
		}
	}
	return ;
}
void	FindWordByPrefix(TrieTreeNode*		pHead,char*		pInput)
{
	char				tempChar='\0';
	int					iIndex=0;
	TrieTreeNode*		pTempHead= NULL;

	if (pHead== NULL || pInput == NULL)
	{
		printf("\nInput String is Incorrect!");
		return ;
	}
	pTempHead = pHead;
	printf("\n");
	if ( pInput[iIndex] >'A' && pInput[iIndex]<'Z')
		tempChar = abs('A'- pInput[iIndex]);
	else 
		tempChar = abs('a'- pInput[iIndex]);
	printf("\n******************\n");
	if ( pTempHead->pChild[tempChar] )
		ExtractWordFromNode(pTempHead->pChild[tempChar]);
	else
	{
		printf("\nHead is NULL! TrieTree is NULL");
		return ;
	}
	printf("\n");
	return ;
}
void ExtractWordFromNode(TrieTreeNode*		pHead)
{
	static char			cPrefixLetter='\0';
	if ( pHead )
	{
		cPrefixLetter = pHead->charValue;
		for ( int iIndex =0; iIndex < MAX_SIZE; iIndex++)
		{
			if ( pHead->pChild[iIndex] )
			{
				printf("%c", pHead->pChild[iIndex]->charValue);
				if ( pHead->pChild[iIndex]->bEndOfWord )
				{
					printf("\n******************\n");
					return;
				}
				else
					ExtractWordFromNode(pHead->pChild[iIndex]);
			}
		}
	}
}
void	FreeTrieTree(TrieTreeNode*		pHead)
{
	TrieTreeNode*		pHeadNode = NULL;
	if ( pHead ==NULL)
	{
		printf("Trie Head node is NULL! Nothing to Free.");
		return;
	}
	pHeadNode = pHead;
	if ( pHeadNode->pChild )
	{
		int iSizeToIterate = sizeof(pHeadNode->pChild)/sizeof(*(pHeadNode->pChild));
		for ( int iIndex = 0; iIndex < iSizeToIterate; iIndex++)
		{
			if ( pHeadNode->pChild[iIndex])
			{
				FreeTrieTree(pHeadNode->pChild[iIndex]);
				delete pHeadNode->pChild[iIndex];
				__iIndex--;
			}
		}
	}
    delete pHead;
	return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	__pTrieHead = new TrieTreeNode();
	InsertValue(__pTrieHead, "truck");
	InsertValue(__pTrieHead, "trick");
	InsertValue(__pTrieHead, "trunck");
	InsertValue(__pTrieHead, "trash");
	InsertValue(__pTrieHead, "tank");
	FindWordByPrefix(__pTrieHead, "t");
	FreeTrieTree(__pTrieHead);
	return 0;
}
