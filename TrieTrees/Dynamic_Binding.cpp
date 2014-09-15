#include <iostream.h>
#include <conio.h>
#include "Dynamic_Binding.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>


//Globacl Tree Root Node...
static TreeNode *__pRoot = NULL;
static TrieTreeNode*	__pTrieHead = NULL;

TrieTreeNode::TrieTreeNode()
{
	printf("\nTrieTreeNode++");
	iIndex =0;
	charValue='\0';
	bEndOfWord = false;
	int iSizeofArray = sizeof(pChild)/sizeof(*pChild);
	//printf("\nSizeofArray is [%d]", iSizeofArray);
	//printf("\nSize of Whole Child Block is :[%d]", sizeof(TrieTreeNode)*iSizeofArray);
	memset(pChild, 0, (sizeof(int) * (sizeof(pChild)/sizeof(*pChild))));
	printf("\nTrieTreeNode--");
}
TrieTreeNode::~TrieTreeNode()
{
	printf("\n~TrieTreeNode++");
	printf("\n~TrieTreeNode--");
}

static int __iIndex= 0;

typedef void (*Fun)(void);

int Abstract::iPrivateStatic = 10;

Abstract::~Abstract()
{
	cout<<"\nAbstract Class pure virtual destructor\n";
}
typedef struct
{
	int		iNowFileIndex;
	char	szFilePath[100];
	int		iStatus;
}NowFileInfo;

typedef struct
{
	int iFileCount;
	NowFileInfo**	ppNowFileInfo;
}ParamNode;


void fn1();
void fn2(NowFileInfo*);
void fn3(ParamNode*);

void fn1()
{
	int nNoOfCharsToCopy =0;
	NowFileInfo UploadFileInfo = {'\0'};
	UploadFileInfo.iNowFileIndex = 5;
	UploadFileInfo.iStatus = 0;
	strcpy(UploadFileInfo.szFilePath , "Photo1");
	nNoOfCharsToCopy = sizeof (UploadFileInfo.szFilePath);
	strncpy(UploadFileInfo.szFilePath,"Photo1", nNoOfCharsToCopy);
	fn2(&UploadFileInfo);
}
void fn2(NowFileInfo* pFileInfo)
{
	ParamNode* pTempParamNode= NULL;
	
	if ( pFileInfo == NULL )
		return;

	printf("File Info : %s", pFileInfo->szFilePath);
	printf("\nFile Status: %d", pFileInfo->iStatus);

	pTempParamNode = (ParamNode*) malloc(sizeof(ParamNode));

	if ( pTempParamNode == NULL )
		return;

	memset(pTempParamNode, 0 ,sizeof( ParamNode ));

	pTempParamNode->iFileCount  = 5;
	pTempParamNode->ppNowFileInfo = (NowFileInfo**) malloc(pTempParamNode->iFileCount * sizeof(NowFileInfo*));

	if ( pTempParamNode == NULL )
		return;

	memset(pTempParamNode->ppNowFileInfo, 0 ,pTempParamNode->iFileCount* sizeof(NowFileInfo*));

	for(int iIndex = 0; iIndex< pTempParamNode->iFileCount ; iIndex++ )
	{
		pTempParamNode->ppNowFileInfo[iIndex] = (NowFileInfo*) malloc(sizeof(NowFileInfo));
		memcpy( pTempParamNode->ppNowFileInfo[iIndex], pFileInfo, sizeof(NowFileInfo));
	}

	fn3(pTempParamNode);
}
void fn3(ParamNode* pParamNode)
{
	if ( pParamNode == NULL )
		return;
	for ( int iIndex = 0 ; iIndex < pParamNode->iFileCount ; iIndex++ )
	{
		printf("\nFile Path : [%s] \n", pParamNode->ppNowFileInfo[iIndex]->szFilePath);
		printf("Now File Id : [%d] \n", pParamNode->ppNowFileInfo[iIndex]->iNowFileIndex);
		printf("File Status : [%d] \n", pParamNode->ppNowFileInfo[iIndex]->iStatus);
	}
	
	for ( iIndex = 0; iIndex < pParamNode->iFileCount ; iIndex++)
	{
		free ( pParamNode->ppNowFileInfo[iIndex]);
		pParamNode->ppNowFileInfo[iIndex] = NULL;
	}
	free(pParamNode);
	pParamNode = NULL;
}

int main()
{
	__pTrieHead = new TrieTreeNode();

	InsertValue(__pTrieHead, "truck");
	InsertValue(__pTrieHead, "trick");
	InsertValue(__pTrieHead, "trunck");
	InsertValue(__pTrieHead, "trash");
	InsertValue(__pTrieHead, "tank");

	/*FindWord(__pTrieHead, "tank");
	FindWord(__pTrieHead, "truck");
	FindWord(__pTrieHead, "trick");
	FindWord(__pTrieHead, "trunck");
	FindWord(__pTrieHead, "trash");

	FindWord(__pTrieHead, "trudt");*/

	FindWordByPrefix(__pTrieHead, "t");

	getch();
	FreeTrieTree(__pTrieHead);
	return 1;

/* Derived d;
	Base* b1 = &d;
	Base& b2 = d;
	Base b3;*/

	/*AccessVTable clAccessVTable;

	int* vptrBase = (int*)&clAccessVTable;
	getch();
	return 0;

	fn1();*/

	// Late binding for both:
	/*cout << "b1->f() = " << b1->f() << endl;
	cout << "b2.f() = " << b2.f() << endl;

	// Early binding (probably):
	cout << "b3.f() = " << b3.f() << endl;

	cout << "VPTR's Address " << (int*)(&d+0) << endl;
	cout << "virtual tables's Address " << (int*)*(int*)(&d+0) << endl; // Value of VPTR
	cout << "Value at first entry of VIRTUAL TABLE " << (int*)*(int*)*(int*)(&d+0) << endl;

	Fun pFun = (Fun)*(int*)*(int*)(&d+0);   // calling Virtual function
	pFun();
	d.fnDisplay();

	/*Derived* pDerivedPtr = new Derived[10];
	Derived* pTempDptr;
	pTempDptr = (pDerivedPtr+5);
	delete [] pTempDptr;

	int i=10;
	int & iRef = i;

	/*Temp *pTemp = new Temp;

	//Allocate memoty for 2Dimensional array and assign value to it...
	Temp** ppTemp = new Temp*[10];

	for ( i =0 ; i < 10 ; i++ )
		ppTemp[i] = new Temp;
	
	memset(ppTemp, 0 , 10 * sizeof (Temp));

	for ( i =0 ; i < 10 ; i++ )
	{
		delete ppTemp[i];
		ppTemp[i] = NULL;
	}
	delete []ppTemp;
	//Allocation of 2D arary on heap ends...



	//Difference between passing reference and pointers as function argument...
	{
		Temp t1;
		t1.iInt = 10;

		//call copy constructor...
		Temp t2 = t1;

		//call pointered copy constructor...
		Temp t3(&t2);
	}
	//Ends...
	
	*/
	//getch();
	char ch='\0';
	int option=0, iValue=0, iDirection=-1;
	do
	{
		printf("\n*****************************");
		printf("\n\tTREE OPERATIONS");
		printf("\n*****************************");
		printf("\n1.Insert Node Element");
		printf("\n2.Delete Node Element");
		printf("\n3.Search Node Element");
		printf("\n4.Find Node Element");
		printf("\n5.InOrder Traversal");
		printf("\n6.PreOrder Traversal");
		printf("\n7.PostOrder Traversal");
		printf("\n8.Is Mirror Image");
		printf("\n9.BFS Traversal");
		printf("\n10.DFS Traversal");
		printf("\n11.Create Mirror Image Tree");
		printf("\n12.Release Tree Nodes");
		printf("\n13.Terminate");
		printf("\n*****************************");
		printf("\nEnter Option : ");
		scanf("%d",&option);
		
		switch ( option )
		{
		case 1:
			{
				printf("\nEnter value:");
				scanf("%d", &iValue);
				InsertTreeNode(&__pRoot, iValue);
			}
			break;
		case 2:
			break;
		case 3:
			{
				clock_t StartTime, EndTime;
				float micro=0.0, seconds=0.0;
				printf("\nEnter value to search:");
				scanf("%d", &iValue);
				StartTime = clock();
				if (!SearchTreeNode(__pRoot, iValue))
					printf("\nNOT FOUND...!!!");
				EndTime= clock();
				micro = ((float)StartTime- (float)EndTime);
				printf("\nTime taken to perform search operation is [%f] microseconds", micro);
				printf("\nTime taken to perform search operation is [%f] seconds", seconds);
			}
			break;
		case 4:
			break;
		case 5:
			{
				TraverseTree_InOrder(__pRoot);
			}
			break;
		case 6:
			{
				TraverseTree_PreOrder(__pRoot);
			}
			break;
		case 7:
			{
				TraverseTree_PostOrder(__pRoot);
			}
			break;

		case 8:
			{
				if ( MirrorImage(__pRoot, NULL, NULL))
					printf("\nTree is Mirro Image.");
				else	
					printf("\nTree is not Mirror Image");
			}	
		break;
		case 9:
			{
				TraverseTree_PostOrder(__pRoot);
			}
		break;
		case 10:
			{
				TraverseTree_PostOrder(__pRoot);
			}
		break;
		case 11:
			{
				printf("\nEnter value:");
				scanf("%d", &iValue);
				printf("\nEnter direction [LEFT =1, RIGHT=1]:");
				scanf("%d", &iDirection);
				CreateMirrorImageTree(&__pRoot, iValue, iDirection);
			}
		break;
		case 12:
			{
				ReleaseTreeNodes(&__pRoot);
					//__pRoot = NULL;
			}
			break;
		}
	}
	while (option<13);
	ReleaseTreeNodes(&__pRoot);
	return 1;
} 
bool InsertTreeNode(TreeNode **ppRootNode, int Value)
{
	bool bRetValue=false;
	TreeNode	*pTempNode = NULL;
	TreeNode	*pNewNode = NULL;

	if (!ppRootNode || !(*ppRootNode)) 
	{
		pNewNode = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNode)
		{
			printf("\n Memory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNode, 0, sizeof(TreeNode));

		pNewNode->data = Value;

		*ppRootNode=pNewNode;

		bRetValue=true;
		goto Catch;
	}
	
	if ( Value < (*ppRootNode)->data )				//Process left subtree...
	{
		if ( (*ppRootNode)->pLeft )
			InsertTreeNode(&(*ppRootNode)->pLeft, Value);
		else
		{
			pNewNode = (TreeNode*) malloc(sizeof(TreeNode));
			if(!pNewNode)
			{
				printf("\nMemory allocation failed, could not continue insertion operations.");
				bRetValue = false;
				goto Catch;
			}
			memset( pNewNode, 0, sizeof(TreeNode));
			pNewNode->data = Value;	
			(*ppRootNode)->pLeft = pNewNode;
		}
		bRetValue = true;
	}
	else if ( Value > (*ppRootNode)->data )			//Process right subtree...
	{
		if ( (*ppRootNode)->pRight)
			InsertTreeNode(&(*ppRootNode)->pRight, Value);
		else
		{
			pNewNode = (TreeNode*) malloc(sizeof(TreeNode));
			if(!pNewNode)
			{
				printf("\nMemory allocation failed, could not continue insertion operations.");
				bRetValue = false;
				goto Catch;
			}
			memset( pNewNode, 0, sizeof(TreeNode));
			pNewNode->data = Value;	
			(*ppRootNode)->pRight = pNewNode;
		}
		bRetValue = true;
	}	
Catch:
	return bRetValue;
}

bool ReleaseTreeNodes( TreeNode** ppRootNode )
{
	bool bRetValue = true;

	if( !ppRootNode || !(*ppRootNode)) 
	{
		printf("\nTree is alrady freed...");
		return false;
	}
	
	if ( (*ppRootNode)->pLeft)
		ReleaseTreeNodes(&(*ppRootNode)->pLeft);
	if ( (*ppRootNode)->pRight)		
		ReleaseTreeNodes(&(*ppRootNode)->pRight);

	if( *ppRootNode )
	{
		free (*ppRootNode);
		*ppRootNode = NULL;
	}
			
	return bRetValue;
}
bool	TraverseTree_InOrder(TreeNode *pRootNode)
{
	bool bRetValue = true;

	if( !pRootNode ) 
	{
		printf("\nTree is alrady freed...");
		return false;
	}
	
	if ( pRootNode->pLeft)
		TraverseTree_InOrder(pRootNode->pLeft);

	printf("%d ", pRootNode->data);

	if ( pRootNode->pRight)		
		TraverseTree_InOrder(pRootNode->pRight);
		
	return bRetValue;
}
bool	TraverseTree_PreOrder(TreeNode *pRootNode)
{
	bool bRetValue = true;

	if( !pRootNode ) 
	{
		printf("\nTree is alrady freed...");
		return false;
	}

	printf("%d ", pRootNode->data);
	
	if ( pRootNode->pLeft)
		TraverseTree_PreOrder(pRootNode->pLeft);
	if ( pRootNode->pRight )
		TraverseTree_PreOrder(pRootNode->pRight);
		
	return bRetValue;
}

bool	TraverseTree_PostOrder(TreeNode *pRootNode)
{
	bool bRetValue = true;

	if( !pRootNode ) 
	{
		printf("\nTree is alrady freed...");
		return false;
	}
	
	if ( pRootNode->pLeft)
		TraverseTree_PostOrder(pRootNode->pLeft);
	if ( pRootNode->pRight)		
		TraverseTree_PostOrder(pRootNode->pRight);

	printf("%d ", pRootNode->data);
			
	return bRetValue;
}

/*
Function Description	: Searches the node having keyvalue equal to the value being asked in the binay search tree.
						this function return true if the node is found, return false if not found.
Function Name			: SearchTreeNode
Function Parameters		: 
			1. pRootNode[TreeNode*] : pointer to the root node of the binary search tree.
			2. iValue[int]			: value fo the searched from binary search tree.
Return value			: 
			[bool] true if searched node is found, false otherwise.
*/
bool	SearchTreeNode(TreeNode* pRootNode, int iValue)
{
	bool bRetValue = false;

	if( !pRootNode ) 
	{
		printf("\nTree is alrady freed...");
		return false;
	}
	
	//1.[RECURSIVE SOLUTION]One of the approach for searching the node in biinary search tree...
	/*
	if ( pRootNode->data == iValue)
	{
		printf("\nVALUE FOUND...!!!");
		bRetValue = true;
		return bRetValue;
	}
	if ( pRootNode->pLeft)
	{
		bRetValue = SearchTreeNode(pRootNode->pLeft, iValue);
		if ( bRetValue )
			return bRetValue;
	}
	if ( pRootNode->pRight)		
	{
		bRetValue = SearchTreeNode(pRootNode->pRight, iValue);
		if ( bRetValue )
			return bRetValue;
	}
	//printf("%d ", pRootNode->data);
	*/

	//2. [NON RECURSIVE/ITERATIVE]approach could be like this
	while ( pRootNode )
	{
		if( pRootNode->data == iValue )
		{
			bRetValue = true;
			break;
		}
		else if ( iValue < pRootNode->data )
			pRootNode = pRootNode->pLeft;
		else if ( iValue >= pRootNode->data )
			pRootNode = pRootNode->pRight;
	}


	return bRetValue;
}
bool MirrorImage(TreeNode* pRootNode, TreeNode* pLeftSubTree, TreeNode* pRightSubTree)
{
	bool bRetValue = false;
	TreeNode* pLeft =NULL, *pRight = NULL;
	
	if ( !pRootNode ) return false;

	if ( pLeftSubTree )
		pLeft= pLeftSubTree;
	else
		pLeft = pRootNode->pLeft;

	if ( pRightSubTree )
		pRight = pRightSubTree;
	else
		pRight = pRootNode->pRight;

	if (pLeft && pRight)
	{
		if ( pLeft->data == pRight->data )
			bRetValue = true;
		else 
		{
			bRetValue = false;
			goto Error;
		}
	}
	else
	{
		bRetValue = false;
		goto Error;
	}

	if ( pLeft->pLeft && pRight->pRight)
	{
		bRetValue = MirrorImage(pRootNode, pLeft->pLeft, pRight->pRight);
		if ( !bRetValue )
			goto Error;
	}
	else if ( pLeft->pRight && pRight->pLeft)
	{
		bRetValue = MirrorImage(pRootNode, pLeft->pRight, pRight->pLeft);
		if ( !bRetValue )
			goto Error;
	}
	else
	{
		printf("Tree is Mirror Image tree...");
		bRetValue= true;
	}
Error:
	return bRetValue;
}


bool DFS(TreeNode *pRootNode)
{
	return true;
}
bool	BFS(TreeNode *pRootNode)
{
	return true;
}

bool CreateMirrorImageTree(TreeNode **ppRootNode, int Value, int iDir)
{
	bool bRetValue=false;
	TreeNode	*pNewNodeLeft, *pNewNodeRight = NULL, *pHeadNode= NULL;

	//create root node...
	if (!ppRootNode || !(*ppRootNode)) 
	{
		pNewNodeLeft = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNodeLeft)
		{
			printf("\n Memory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNodeLeft, 0, sizeof(TreeNode));
		pNewNodeLeft->data = Value;
		*ppRootNode=pNewNodeLeft;

		bRetValue=true;
		goto Catch;
	}
	
	//create child nodes...
	pHeadNode = *ppRootNode;
	if ( iDir == 0 )			//left 
	{
		//1. Cretae Left Child node...
		while ( pHeadNode->pLeft != NULL )
			pHeadNode = pHeadNode->pLeft;

		pNewNodeLeft = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNodeLeft)
		{
			printf("\n Memory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNodeLeft, 0, sizeof(TreeNode));
		pNewNodeLeft->data = Value;
		pHeadNode->pLeft = pNewNodeLeft;
		///left child added

		//2. Create right child...
		pHeadNode = *ppRootNode;
		while ( pHeadNode->pRight!= NULL )
			pHeadNode = pHeadNode->pRight;

		pNewNodeRight = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNodeRight)
		{
			printf("\nMemory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNodeRight, 0, sizeof(TreeNode));
		pNewNodeRight->data = Value;	
		pHeadNode->pRight = pNewNodeRight;
		//right child added
	}

	else if ( iDir ==1 )			//right
	{
		//1. Cretae Left Child node...
		while ( pHeadNode->pLeft != NULL )
			pHeadNode = pHeadNode->pLeft;

		pNewNodeLeft = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNodeLeft)
		{
			printf("\n Memory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNodeLeft, 0, sizeof(TreeNode));
		pNewNodeLeft->data = Value;
		pHeadNode->pRight = pNewNodeLeft;
		///left child added

		//2. Create right child...
		pHeadNode = *ppRootNode;
		while ( pHeadNode->pRight!= NULL )
			pHeadNode = pHeadNode->pRight;

		pNewNodeRight = (TreeNode*) malloc(sizeof(TreeNode));
		if(!pNewNodeRight)
		{
			printf("\nMemory allocation failed, could not continue insertion operations.");
			bRetValue = false;
			goto Catch;
		}
		memset( pNewNodeRight, 0, sizeof(TreeNode));
		pNewNodeRight->data = Value;	
		pHeadNode->pLeft = pNewNodeRight;
		//right child added
	}
	bRetValue = true;
Catch:
	return bRetValue;
}

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