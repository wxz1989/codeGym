#include  <iostream>

using namespace std;

struct Node{

	int data;
	Node* next;
};

typedef Node* NodePtr;
typedef Node** NodeDPtr;

void PrintList(NodePtr pHead);
bool RecCompare(NodeDPtr pHead, NodePtr pMid, NodePtr pCmp);
bool PalindromList(NodePtr pHead);

void PrintList(NodePtr pHead){
	while ( pHead != NULL){
		cout <<pHead->data<<" ";
		pHead = pHead->next;
	}
	cout<< endl;
}

bool RecCompare(NodeDPtr pHead, NodePtr pMid, NodePtr pCmp){
	bool bRet = false;

	if ( *pHead == NULL ){ return false; }
	if ( *pHead == pMid ){  return bRet; }
	if ( pCmp == NULL ){ return true; }

	bRet = RecCompare(pHead, pMid, pCmp->next);
	if ( bRet == true){
		if ( (*pHead)->data == pCmp->data){
			*pHead = (*pHead)->next;
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
	if ( pHead->next == NULL){		//Single Node
		return false;
	} 
	if( pHead->next->next == NULL){	//Two Nodes.
		if( pHead->data == pHead->next->data){
			return true;
		} else {
			return false;
		}
	}
	if( pHead->next->next->next == NULL){  //Three Nodes
		if( pHead->data == pHead->next->next->data){
			return true;
		} else {
			return false;
		}
	}
	int iE=0, iM=0, Count=0;
	pM = pE = pHead;
	//Find mid, end and counts of the list.

	while ( true ){
		if ( pE->next != NULL ){
			if ( pE->next->next!= NULL ){
				pE = pE->next->next;
				iE++;
				pM = pM->next;
				iM++;
			} else { 
				pE = pE->next;
				iE++;
				break;
			}
		} else {
			break;
		} 
	}
	Count = (iE + iM) +1;

	if ( (Count %2) == 0 ){		//Even No of Elements in the list
		if( pM->data != pM->next->data){
			return false;
		} else {
			return RecCompare(&pHead, pM, pM->next->next);
		}
	} else {					//Odd No of Elements in the list
		return RecCompare(&pHead, pM, pM->next); 
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
			pNew->next = NULL;

			if ( pHead == NULL){
				pHead = pNew;
			} else {
				pLast->next = pNew;
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