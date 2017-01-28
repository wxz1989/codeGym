#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct Node
{
    int iData
    Node*       pNext;
}LinkedListNode;

typedef LinkedListNode*        NodePtr;
typedef LinkedListNode**        NodeDPtr;
NodePtr pHeadNode = NULL;

void        AddToList(NodeDPtr pHeadNode, int iData);
void 		PrintList(NodePtr pHeadNode);
bool        ClearList(NodePtr pHeadNode);
void 		RemoveDuplicateNode(NodePtr pHeadNode);		//Function removing duplicate node from unsorted list.

bool        HasKNodes(int K, int NodeToSwap, NodePtr  pHeadNode);
NodePtr     ReverseKthNode(int index, int K, NodeDPtr   pHeadNode, NodeDPtr pNewListHead, NodeDPtr pNextNodeToJump);

bool CloneLinkedList(

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
	int i = 0;
	if ( pHeadNode == NULL )
		return;

	NodePtr tempNode;
	tempNode = pHeadNode;

	//Approach:1 First find out size of the linked list first.. create an arary of same size, keep updating a flag of all visited nodes.
	int iSize = 0;
	while ( tempNode  != NULL )
	{
		iSize++;
		tempNode = tempNode->pNext;
	}
	std::cout<<"Total nodes : "<< iSize<<endl;
	bool bSize[iSize];			//by this time time complexity is already O(n) reached and space complexity has also become O(2*n)

	for ( i =0; i < iSize ; i++ )
		bSize[i] =0;

	i = 0;
	iSize =0;

	NodePtr tmpNode;
	tmpNode = pHeadNode;
	while ( tmpNode != NULL )
        {
		std::cout<<"Curent Index ["<<iSize<<"]";
                tmpNode = tmpNode->pNext;
		if ( bSize[iSize] == 1 )
                {
                        std::cout<<"Duplicate node at "<<"["<<i<<"] found"<<endl;
			bSize[iSize]  = -1;
                }
                else
			bSize[iSize] = 1;			//Assuming the data is only in form of integers.
		iSize++;
        }
	std::cout<<"Total Nodes:"<<iSize<<endl;
	std::cout<<"Nodes visited are following:"<<endl;

	for ( i =0; i < iSize ; i++ )
	{
		std::cout<<"["<< i<<"]"<<bSize[i]<<endl;
	}
	iSize =0;
}
