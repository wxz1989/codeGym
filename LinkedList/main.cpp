#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

typedef struct Node
{
    int iData;
    Node*       pNext;
}LinkedListNode;

typedef LinkedListNode*        NodePtr;
typedef LinkedListNode**        NodeDPtr;
NodePtr pHeadNode = NULL;

void        	AddToList(NodeDPtr pHeadNode, int iData);
void 		PrintList(NodePtr pHeadNode);
bool        	ClearList(NodePtr pHeadNode);
void 		RemoveDuplicateNode(NodePtr pHeadNode);		//Function removing duplicate node from unsorted list.

bool        HasKNodes(int K, int NodeToSwap, NodePtr  pHeadNode);
NodePtr     ReverseKthNode(int index, int K, NodeDPtr   pHeadNode, NodeDPtr pNewListHead, NodeDPtr pNextNodeToJump);

int main(int argc, const char * argv[])
{
    int Array[50] = {0}, iNoOfNodes = 0;
	std::cout <<"No of Nodes: ";
	scanf("%d", &iNoOfNodes);

    for ( int i = 0; i < iNoOfNodes ; i++)
        scanf("%d", &Array[i]);

	for ( int i = 0; i < iNoOfNodes ; i++)
        AddToList(&pHeadNode, Array[i]);

	std::cout<<"Printing ListNode"<<endl;
	PrintList(pHeadNode);
	std::cout<<endl;	
	std::cout<<"Remove DuplicateNode"<<endl;
	RemoveDuplicateNode(pHeadNode);
	std::cout<<endl;
	std::cout<<"Clearing ListNode"<<endl;
	ClearList(pHeadNode);
	std::cout<<endl;
    return 0;
}

void
AddToList(NodeDPtr pHeadNode, int iData){

	stack<int> mystack;
	list<int> locallist;
	queue<int> localQueue;

    NodePtr pNewNode = NULL, pTempNode = NULL;
    pTempNode = *pHeadNode;
    pNewNode = new (std::nothrow) LinkedListNode();

    if ( pNewNode != NULL ){

        pNewNode->iData = iData;
        pNewNode->pNext = NULL;

        if ( *pHeadNode== NULL){
            *pHeadNode = pNewNode;
        }
        else{
            while ( pTempNode->pNext !=NULL ) {
                pTempNode  = pTempNode->pNext;
            }
            pTempNode->pNext = pNewNode;
        }
    }
}

bool
HasKNodes(int K, int NodeToSwap, NodePtr  pHeadNode){
    return true;
}

NodePtr
ReverseKthNode(int index, int K, NodeDPtr   pHeadNode, NodeDPtr pNewListHead, NodeDPtr pNextNodeToJump)
{
    return NULL;
}


void PrintList(NodePtr pHeadNode)
{
	if ( pHeadNode == NULL )
        	return;
	std::cout<<pHeadNode->iData<<" ";	
	PrintList(pHeadNode->pNext);
}
bool
ClearList(NodePtr pHeadNode){

    if ( pHeadNode == NULL )
        return false;

    if( pHeadNode->pNext!= NULL )
        ClearList(pHeadNode->pNext);

    std::cout<<pHeadNode->iData<<" ";
    delete pHeadNode;
    return true;
}

void RemoveDuplicateNode(NodePtr pHeadNode)
{
	if ( pHeadNode == NULL )
		return;

	//Approach:1 First find out size of the linked list first.. create an arary of same size, keep updating a flag of all visited nodes.
	int iSize = 0;
	while ( pHeadNode != NULL )
	{
		iSize++;
		pHeadNode = pHeadNode->pNext;
	}
	std::cout<<"Total nodes : "<< iSize;
	bool bSize[iSize];			//by this time time complexity is already O(n) reached and space complexity has also become O(2*n)

	iSize =0;
	while ( pHeadNode != NULL )
        {
                pHeadNode = pHeadNode->pNext;
		bSize[iSize++] = 1;			//Assuming the data is only in form of integers.
        }
	std::cout<<endl;
	for ( int i =0; i < iSize ; i++ )
	{
		std::cout<<"["<< i<<"]"<<bSize[i];
	}
	std::cout<<endl;
	iSize =0;
}
