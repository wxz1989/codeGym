#include  <iostream>

using namespace std;

struct Node{

	int data;
	Node* pNext;
};

typedef Node* NodePtr;
typedef Node** NodeDPtr;

void PrintList(NodePtr pHead);
bool RecCompare(NodeDPtr pHead, NodePtr pMid, NodePtr pCmp);
bool PalindromList(NodePtr pHead);

void PrintList(NodePtr pHead){
	while ( pHead != NULL){
		cout <<pHead->data<<" ";
		pHead = pHead->pNext;
	}
	cout<< endl;
}

bool RecCompare(NodeDPtr pHead, NodePtr pMid, NodePtr pCmp){
	bool bRet = false;

	if ( *pHead == NULL ){ return false; }
	if ( *pHead == pMid ){  return bRet; }
	if ( pCmp == NULL ){ return true; }

	bRet = RecCompare(pHead, pMid, pCmp->pNext);
	if ( bRet == true){
		if ( (*pHead)->data == pCmp->data){
			*pHead = (*pHead)->pNext;
			return true;
		} else {
			return false;
		}
	}
	return bRet;
}

bool PalindromList(NodePtr pHead){

	NodePtr pM = NULL, pE = NULL;
	//Initial Checks...
	if ( pHead == NULL ){			//Empty
		return false;
	} 
	if ( pHead->pNext == NULL){		//Single Node
		return false;
	} 
	if( pHead->pNext->pNext == NULL){	//Two Nodes.
		if( pHead->data == pHead->pNext->data){
			return true;
		} else {
			return false;
		}
	}
	if( pHead->pNext->pNext->pNext == NULL){  //Three Nodes
		if( pHead->data == pHead->pNext->pNext->data){
			return true;
		} else {
			return false;
		}
	}
	int iE=0, iM=0, Count=0;
	pM = pE = pHead;
	//Find mid, end and counts of the list.

	while ( true ){
		if ( pE->pNext != NULL ){
			if ( pE->pNext->pNext!= NULL ){
				pE = pE->pNext->pNext;
				iE++;
				pM = pM->pNext;
				iM++;
			} else { 
				pE = pE->pNext;
				iE++;
				break;
			}
		} else {
			break;
		} 
	}
	Count = (iE + iM) +1;

	if ( (Count %2) == 0 ){		//Even No of Elements in the list
		if( pM->data != pM->pNext->data){
			return false;
		} else {
			return RecCompare(&pHead, pM, pM->pNext->pNext);
		}
	} else {					//Odd No of Elements in the list
		return RecCompare(&pHead, pM, pM->pNext); 
	}

}

int main(){

	int T;
	freopen("Palindrom_sample_input.txt", "r", stdin);

	int Length;
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
			pNew->pNext = NULL;

			if ( pHead == NULL){
				pHead = pNew;
			} else {
				pLast->pNext = pNew;
			}
			pLast= pNew;
		}

		PrintList(pHead);

		if (PalindromList(pHead) == true ){
			cout <<"Palindrome"<<endl;
		} else{
			cout <<"No Palindrome"<<endl;		
		}
	}
	return 0;
}