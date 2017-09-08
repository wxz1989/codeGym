#include <iostream>
#include <memory>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <time.h>

#include "BinaryTree.h"

using namespace std;


int main()
{
	ifstream sampleInputFile ("BTSampleInput.txt");
	char ch='\0';
	int option=0, iValue=0, iDirection=-1;
	do
	{
		printf("\n*****************************");
		printf("\n\tTREE OPERATIONS");
		printf("\n*****************************");
		cout << endl;
		cout << "0. Build from Sample input file" << endl;
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
		cout <<  endl;
		cout << "14. InOrder Successor" << endl;
		printf("\n*****************************");
		printf("\nEnter Option : ");
		scanf("%d",&option);
		
		switch ( option )
		{
			case 14:{
				int inputValue;
				cout << "Enter Value:"<< endl;
				cin >> inputValue;		
			}
			break;
			case 0:{
				int test_cases;
				int size;
				std::string inputString;

				if (sampleInputFile.is_open()){
				//Converting String to Number using getline
					getline (sampleInputFile,inputString);

					//cout << "getline test_cases:[" << inputString << "]" << endl;
	// This code converts from string to number safely.
					stringstream myStream(inputString);

					if ( myStream >> test_cases ){
						//cout << "Test cases :[" << test_cases << "]" <<  endl;
					} 

				//Converting String to Number using getline
					getline (sampleInputFile,inputString);

					//cout << "getline size:[" << inputString << "]" << endl;
	// This code converts from string to number safely.
					stringstream sizeStream(inputString);

					if ( sizeStream >> size ){
						//cout << "TC Size:[" << size << "]" <<  endl;
					} 


					while ( getline (sampleInputFile,inputString) ) {
						int intValue;
						std::istringstream iss(inputString);
						while( iss >> intValue){
							InsertTreeNode(&__pRoot, intValue);	
						}
					}
					sampleInputFile.close();
				} else { cout << "Unable to open Sample Input File" << endl; return -1; }
			}
			break;
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
