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

void        AddToList(NodeDPtr pHeadNode, int iData);
void 		PrintList(NodePtr pHeadNode);
bool        ClearList(NodePtr pHeadNode);
void 		RemoveDuplicateNode(NodePtr pHeadNode);		//Function removing duplicate node from unsorted list.

bool        HasKNodes(int K, int NodeToSwap, NodePtr  pHeadNode);

NodePtr     ReverseKNodes(NodePtr   pHeadNode, int val);
NodePtr     ReverseKUtil(NodePtr   pHeadNode, NodeDPtr pNH, NodeDPtr pNxt, int val, int k);

NodePtr Reverse_Recurse(NodePtr pHead, NodeDPtr pNewHead);
NodePtr Reverse_Recursive(NodePtr pHead, NodeDPtr pNH, int c);

//CTCI LinkedLIst
int KthNodeFromEnd(NodePtr pHead, int k );

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
	/*std::cout<<"Remove DuplicateNode"<<endl;
	RemoveDuplicateNode(pHeadNode);
	std::cout<<endl;
	int kNOde = -1;
	std::cout<<"Enter KThNode from End:"<<endl;
	cin >>  kNOde;
	KthNodeFromEnd(pHeadNode, kNOde);
	std::cout<<"Clearing ListNode"<<endl;

	std::cout<<"Reverse LinkedList With recursion"<<endl;
	NodePtr  pNewHead = nullptr;
	//Reverse_Recurse(pHeadNode, &pNewHead);
	//PrintList(pNewHead);
	pHeadNode = Reverse_Recursive(pHeadNode, &pNewHead, 0);
	PrintList(pHeadNode);
	std::cout<<std::endl;
	std::cout<<"Reverse Complete"<<endl;*/

	int k = 0;
	std::cout<<"Reverse K Nodes "<<endl;
	cin >> k;
	pHeadNode = ReverseKNodes(pHeadNode, k);
	PrintList(pHeadNode);
	cout << endl;
	std::cout<<"Reverse K Nodes Complate "<<endl;

	std::cout<<"Deleting List "<<endl;
	ClearList(pHeadNode);
	cout << endl;
	std::cout<<"Deleting Complete "<<endl;
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
    pNewNode->pNext = nullptr;
    
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

NodePtr     ReverseKNodes(NodePtr   pHeadNode, int k){
	
	if (pHeadNode == nullptr){ return nullptr; }
	if( k <=1) { cout << "No Change Required" << endl; return pHeadNode;}

	NodePtr pNH = nullptr, pNxt = nullptr;
	NodePtr pNewHead = nullptr, pPast = nullptr;

	while ( pHeadNode != nullptr && pHeadNode->pNext != nullptr ){
		NodePtr pR = nullptr;

		pR = ReverseKUtil(pHeadNode, &pNH, &pNxt, k, k);

		if ( pNewHead == nullptr){
			pNewHead = pR;
		}
		if ( pPast != nullptr){
			pPast->pNext = pR; //can use *pNH
		}
		pPast = pHeadNode;
		pHeadNode = pNxt;

		pNH = nullptr;
		pNxt = nullptr;
	}
	return pNewHead;
}

NodePtr     ReverseKUtil(NodePtr   pHeadNode, NodeDPtr pNH, NodeDPtr pNxt, int val, int k){

	cout << "Rev K Util:["<< pHeadNode->iData << "]" << endl;
	cout << "Val:["<< val << "]" << endl;

	if ( pHeadNode == nullptr ){ return nullptr; }

	/*
		Very Important check : 
		If remaining nodes are less than K but greater than terminating condition of Val == 1 would fail
	 	and null value of pHeadNode becuase the folowing check wasn't there 
	 */
	if( pHeadNode->pNext == nullptr){
		*pNxt = nullptr;
		if ( *pNH == nullptr ){
			*pNH = pHeadNode;
		}
		pHeadNode->pNext = nullptr;
		return pHeadNode;
	}

	if ( val == 1){
		*pNxt = pHeadNode->pNext;
		if ( *pNH == nullptr ){
			*pNH = pHeadNode;
		}
		pHeadNode->pNext = nullptr;
		return pHeadNode;
	}

	NodePtr pRet = ReverseKUtil(pHeadNode->pNext, pNH, pNxt, val-1, k);
	
	if( pRet != nullptr ) {  pRet->pNext = pHeadNode; }

	if ( val == k ){
		pHeadNode->pNext = *pNxt;
		return *pNH;
	}
	return pHeadNode;
}


NodePtr Reverse_Recurse(NodePtr pHead, NodeDPtr pNewHead){

	if ( pHead == nullptr ){ return pHead; }
	NodePtr pRet =  Reverse_Recurse(pHead->pNext, pNewHead);
	pHead->pNext = nullptr;
	if (pRet == nullptr){ *pNewHead = pHead; } 
	else { pRet->pNext = pHead; }
	return pHead;
}


NodePtr Reverse_Recursive(NodePtr pHead, NodeDPtr pNH, int c){
	cout << "Head:["<< pHead->iData << "]" << endl;
	if ( pHead == nullptr) { return nullptr; }
	if( pHead->pNext == nullptr) { 
		cout << "New Head" << endl;
		*pNH = pHead ; 	
		return pHead;
	}

	//(NodePtr(Reverse_Recursive(pHead->pNext, pNH, c+1))->pNext = pHead;
	NodePtr pRet = Reverse_Recursive(pHead->pNext, pNH, c+1);
	pRet->pNext = pHead;

	if( c == 0 ){ 
		pHead->pNext = nullptr; 
		return *pNH; 
	}
	return pHead;
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

int KthNodeFromEnd(NodePtr pHead, int k ){


	if ( pHead == nullptr){
		return 0;
	}

	int index = KthNodeFromEnd(pHead->pNext, k) + 1;
	if (index == k ){
		cout << "KTh Node from End is :[" << pHead->iData <<"]" << endl;
	}
	return index;
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
		//std::cout<<"Curent Index ["<<iSize<<"]";
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
