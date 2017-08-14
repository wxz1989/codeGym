#include <iostream>
#include <stdio.h>

using namespace std;

struct Node{

	int data;
	Node* next;
};

typedef Node* NodePtr;
typedef Node** NodeDPtr;


void PrintList(NodePtr pHead){
	while ( pHead != NULL){
		cout <<pHead->data<<" ";
		pHead = pHead->next;
	}
	cout << endl;
}


void ReArrangeList(NodeDPtr pHead){

	if ( pHead == NULL && *pHead == NULL ){ return; }

	NodePtr pTemp = *pHead;
	NodePtr pPOI = NULL;

	while ( pTemp != NULL){

		if ( pTemp->data % 2 == 0 ){
			pPOI = pTemp;
			pTemp = pTemp->next;
			continue;
		}
		if ( pTemp->next != NULL && ((pTemp->next->data)%2 == 0) ){
			 NodePtr pFound = pTemp->next;

			 pTemp->next = pFound->next;

			 if ( pPOI == NULL ){
			 	pFound->next = *pHead;
			 	*pHead = pFound;
			 	pPOI = pFound;
			 } else {
			 	pFound->next = pPOI->next;
			 	pPOI->next = pFound;
			 	pPOI = pPOI->next;// OR pPOI = pFound;
			 }
		} else {
			pTemp = pTemp->next;
		}
	}
}


int ReArrangeList1(NodeDPtr pHead){

	if ( pHead == NULL && *pHead == NULL ){ return -1; }

	NodePtr pTemp = *pHead;
	NodePtr pPrev = NULL;
	NodePtr pLast = NULL;

	int count = 1;
	while( pTemp->next != NULL ){ pTemp = pTemp->next; ++count; }

	pLast = pTemp;
	pTemp = *pHead;

	//while (  pTemp != NULL ){			//this doesn't work, becuase processed nodes are processed again
										// when they are encountered before end of ths list and it can keep looping, 
										// by making change in node structure or by keeping visiting nodes we can keep != NULL check 
	while (  count != 0){
		if ( pTemp->data % 2 != 0 ){
			NodePtr pOdd = pTemp;		
			if ( pPrev == NULL ){
				*pHead = pTemp->next;
				pTemp = *pHead;
			} else {
				pPrev->next = pTemp->next;	
				pTemp = pTemp->next;		
			}
			pLast->next = pOdd;
			pOdd->next = NULL;
			pLast = pOdd;
		} else {
			pPrev = pTemp;
			pTemp = pTemp->next;
		}
		count--;
		
	}
	return 0;
}


int main() {
	int T;
	int Length;
	freopen("ReArrangeListSampleInput.txt","r", stdin);

	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++)
	{
		NodePtr pHead = NULL, pNew = NULL, pLast = NULL;
		cin >> Length;
		
		cout << "Tc#" <<  test_case << endl;
		if ( Length <=0 ){ std::cout <<-1 << endl; continue; }

		for ( int i = 0;i < Length; i++){
			int data;
			cin >> data;

			pNew = new Node();
			pNew->data = data;
			pNew->next = NULL;

			if ( pHead == NULL){
				pHead = pNew;
			} else {
				pLast->next = pNew;
			}
			pLast= pNew;
		}


		if( ReArrangeList1(&pHead) == -1){ std::cout <<-1 << endl; } 
		else { PrintList(pHead); }

	}
	return 0;
}
