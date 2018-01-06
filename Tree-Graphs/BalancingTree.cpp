#include <iostream>
#include <climits>
#include <assert.h>
//#include <bits/stdc++.h>
#include <time.h>
#include <vector>

#define MAX_NODES 100
int ind =0;
int ar[MAX_NODES] ={0};
int balanced[MAX_NODES] ={0};

#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();

struct Node{
	int data;
	int height;	
	int rC, lC;			//For Maintaining the Balance Factor of the Tree, lC=>left children count of the node, rC=>right children count of the node
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

	if( _pRoot == nullptr){  _pRoot = CreateNode(value); return; }
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
	balanced[ind++] = pR->data;
	//cout << pR->data <<" " ;
	InOrder(pR->pRight);
}

void PreOrder(NodePtr pR){
	if(pR == nullptr){ return;  }
	cout << pR->data << " ";
	PreOrder(pR->pLeft);
	//cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC <<endl;
	//balanced[ind++] = pR->data;
	PreOrder(pR->pRight);	
}
void PostOrder(NodePtr pR){
	if(pR == nullptr){ return;  }
	PostOrder(pR->pLeft);
	//cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC <<endl;
	//balanced[ind++] = pR->data;
	PostOrder(pR->pRight);
	cout << pR->data << " ";
}

void PrintBalancedTree(){
	cout << "Balanced BST" << endl;
	for(int i = 0; i< ind; i++){
		cout << balanced[i] << " ";
	}
	cout << endl;
}

void BalanceUtil(NodePtr pR,int low,int high){
	
	if(low >= high){ return;  }
	int mid = (low + high) /2;

	//cout << "Bal Inserting:[" << balanced[mid] <<"]" << endl;
	Insert(_pRoot,balanced[mid]);

	BalanceUtil(pR,low,mid);
	BalanceUtil(pR,mid+1,high);
}
NodePtr Balance(){
	
	if(ind  == 0){ return nullptr;  }

	int low = 0; 
	int high = ind;
	
	Release(_pRoot);
	BalanceUtil(_pRoot,low,high);

	//Clear Balalnced Array and make ind 0// Imp for my logic not for the algo
	memset(balanced,0,sizeof(int)*ind);
	ind = 0;
	// ends 

	InOrder(_pRoot);
	PrintBalancedTree();
	return nullptr;
}

NodePtr InOrderSuc(NodePtr pR,int value){
	return nullptr;
}

NodePtr InOrderPred(NodePtr pR,int value){
	return nullptr;
}

void Test_SampleInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	//cout << "Reading Sample Inputs" <<  endl;
	freopen("BalancingTree_Sample_Input.txt", "r", stdin);
	cin >> test_cases;

	cout << "#TCs" << test_cases <<  endl;
	for (int tc = 0; tc < test_cases; tc++){
		cin >> size;
		for (int i = 0; i < size; i++){ 
			cin >> A[i]; 

			Insert(_pRoot, A[i]);
		}
		InOrder(_pRoot);
		PrintBalancedTree();
		Release(_pRoot);
	}
	Balance();
	PrintBalancedTree();
	cout << "PreOrder:" << endl;
	PreOrder(_pRoot);
	cout << endl;
	cout << "PostOrder:" << endl;
	PostOrder(_pRoot);
	cout << endl;
	
	Release(_pRoot);
}
void Test_RandomisedDataInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(nullptr));
	size = rand() % 20;
	srand(time(nullptr));

	for (int i = 0; i< size; i++){
		int value = rand() % MAX_ARRAY_SIZE;
		A[i] = value;

		cout << "Random Node:["<< value <<"]" << endl;
		Insert(_pRoot,value);
	}
	InOrder(_pRoot) ;
	PrintBalancedTree();
	Balance();
	Release(_pRoot);
}

int main(int argc, char* argv[]){

	cout << "Arg Count:" << argc << endl;
	if (argc > 1){
		cout << "Arg :" << argv[1] << endl;
		if (strcmp(argv[1], "0") == 0){
			Test_SampleInput();
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput();
		}
		else {
			Test_SampleInput();
		}
	} else {
		Test_SampleInput();
	}
	return 0;
}
