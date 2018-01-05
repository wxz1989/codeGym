#include <iostream>
#include <climits>
#include <assert.h>
#include <conio.h>
//#include <bits/stdc++.h>

#define MAX_NODES 100
int ar[MAX_NODES] ={0};

using namespace std;

struct Node{
	int data;
	int height;	
	int rC, lC;
	Node* pLeft,*pRight;
};

typedef struct Node* NodePtr;
NodePtr  _pRoot = nullptr;

NodePtr CreateNode(int value){
	NodePtr pTemp = new struct Node;
	pTemp->height = pTemp->lC = pTemp->rC = 0;
	pTemp->pLeft = pTemp->pRight = nullptr;
	pTemp->data = value;
	return pTemp;
}

void Insert(NodePtr pR,int value){

	if( _pRoot == nullptr){ 
		pR = CreateNode(value);  
		_pRoot = pR; 
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
	//cout << pR->data <<" " ;
	InOrder(pR->pRight);
}

//Sample input 
//30 20 12 28 60 50 90 120 121 122 123 124 125 126 127 128 129 130

void Release(NodePtr pR){

	if(pR == nullptr){ return; }
	Release(pR->pLeft);
	Release(pR->pRight);
	//cout << "Delete:["<< pR->data << "]" << endl; 
	pR->pLeft = nullptr;
	pR->pRight = nullptr;
	delete pR;
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
		Release(_pRoot);
		_pRoot = nullptr;
	}
	_getch();
	return 0;
}
