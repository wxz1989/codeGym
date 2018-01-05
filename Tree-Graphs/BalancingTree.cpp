#include <iostream>
#include <climits>
#include <assert.h>
#include <conio.h>
//#include <bits/stdc++.h>

#define MAX_NODES 100
int index =0;
int ar[MAX_NODES] ={0};
int balanced[MAX_NODES] ={0};

using namespace std;

struct Node{
	int data;
	int height;	
	int rC, lC;
	Node* pLeft,*pRight;
};

typedef struct Node Node;
typedef struct Node* NodePtr;
NodePtr  _pRoot = nullptr;

NodePtr CreateNode(int value){
	NodePtr pTemp = new Node();
	pTemp->height = pTemp->lC = pTemp->rC = 0;
	pTemp->pLeft = pTemp->pRight = nullptr;
	pTemp->data = value;
	return pTemp;
}

void ReleaseUtil(NodePtr pR){

	if(pR == nullptr){ return; }
	ReleaseUtil(pR->pLeft);
	ReleaseUtil(pR->pRight);
	//cout << "Delete:["<< pR->data << "]" << endl; 
	pR->pLeft = nullptr;
	pR->pRight = nullptr;
	delete pR;
}

void Release(NodePtr pR){

	if(pR == nullptr){ return; }
	ReleaseUtil(pR);
	_pRoot = nullptr;
}

void Insert(NodePtr pR,int value){

	if( _pRoot == nullptr){ 
		_pRoot = CreateNode(value);
		return;
	}

	if( pR == nullptr){ return; }
	
	if( value < pR->data ){
		if( pR->pLeft != nullptr){ Insert(pR->pLeft,value); }
		else { pR->pLeft = CreateNode(value); }
		pR->lC += 1;
	} else {
		if( pR->pRight != nullptr){ Insert(pR->pRight,value);}
		else { pR->pRight= CreateNode(value); }
		pR->rC += 1;
	}
}

void InOrder(NodePtr pR){

	if(pR == nullptr){ return;  }
	InOrder(pR->pLeft);
	cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC <<endl;
	balanced[index++] = pR->data;
	//cout << pR->data <<" " ;
	InOrder(pR->pRight);
}

void PrintBalancedTree(){
	cout << "Balanced BST" << endl;
	for(int i = 0; i< index; i++){
		cout << balanced[i] << " ";
	}
	cout << endl;
}

void BalanceUtil(NodePtr pR,int low,int high){
	
	if(low >= high){ return;  }
	int mid = (low + high) /2;

	cout << "Bal Inserting:[" << balanced[mid] <<"]" << endl;
	Insert(_pRoot,balanced[mid]);

	BalanceUtil(pR,low,mid);
	BalanceUtil(pR,mid+1,high);
}
NodePtr Balance(){
	
	if(index  == 0){ return nullptr;  }
	
	Release(_pRoot);

	int low = 0; 
	int high = index;

	BalanceUtil(_pRoot,low,high);

	//Clear Balalnced Array and make index 0// Imp for my logic not for the algo
	memset(balanced,0,sizeof(int)*index);
	index = 0;
	// ends 

	InOrder(_pRoot);
	PrintBalancedTree();
	return nullptr;
}

//Sample input 
/*
18
30 20 12 28 60 50 90 120 121 122 123 124 125 126 127 128 129 130
5
10 20 30 40 50
5
50 40 30 20 10
*/

NodePtr InOrderSuc(NodePtr pR,int value){
	return nullptr;
}

NodePtr InOrderPred(NodePtr pR,int value){
	return nullptr;
}

　
int main(){
	
	int test_cases;
	cin >> test_cases;
	for(int tc = 0; tc< test_cases; tc++){
		int N = 0;
		cin >> N;
		for(int i = 0; i< N;i++){
			cin >> ar[i];
			Insert(_pRoot,ar[i]);
		}
		InOrder(_pRoot) ;
		cout << endl;
		PrintBalancedTree();
		Balance();

		Release(_pRoot);
	}
	_getch();
	return 0;
}
