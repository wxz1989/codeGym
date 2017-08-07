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

int main() {
	int T;
	int Length;
	freopen("ReArrangeListSampleInput.txt","r", stdin);

	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++)
	{
		NodePtr pHead = NULL, pNew = NULL, pLast = NULL;
		cin >> Length;
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
		ReArrangeList(&pHead);
		PrintList(pHead);
	}
	return 0;
}
