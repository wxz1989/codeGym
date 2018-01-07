#include <iostream>
#include <climits>
#include <assert.h>
//#include <bits/stdc++.h>
#include <time.h>
#include <vector>
#include <stack>
#include <queue>

#define MAX_NODES 100
int ind =0;
int ar[MAX_NODES] ={0};
int balanced[MAX_NODES] ={0};
int level = 0;

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
	pTemp->pLeft =  nullptr; 
	pTemp->pRight = nullptr;
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

int leftHeight =0, rightHeight = 0;
void Insert(NodePtr pR,int value){

	if( _pRoot == nullptr){  _pRoot = CreateNode(value); return; }
	if( pR == nullptr){ return; }
	
	if( value < pR->data ){
		if( pR->pLeft != nullptr){
			//cout << "Child:["<< value <<"] Parent:[" << pR->data <<"] Child Height:[" << pR->pLeft->height <<"], Parent Height:[" << pR->height << "]" << endl;
			pR->pLeft->height = pR->height+1;   
			Insert(pR->pLeft,value); 
		}
		else { pR->pLeft = CreateNode(value); }
		pR->lC += 1;
	} else {
		if( pR->pRight != nullptr){ 
			//cout << "Child:["<< value <<"] Parent:[" << pR->data << "] Child Height:[" << pR->pRight->height <<"], Parent Height:[" << pR->height << "]" << endl;
			pR->pRight->height = pR->height+1;   
			Insert(pR->pRight,value);
		}
		else { pR->pRight= CreateNode(value); }
		pR->rC += 1;
	}
}

void InOrder(NodePtr pR){

	if(pR == nullptr){ return;  }
	InOrder(pR->pLeft);
	cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC << "-" << pR->height <<endl;
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

void InOrder_Stack(NodePtr pR){

	if ( pR == nullptr ){ return; }
	stack<NodePtr> traStk;
	int done = 0;
	NodePtr pCrawler = pR;
	while ( !done ){ 
		if ( pCrawler != nullptr ){
			traStk.push(pCrawler);
			pCrawler = pCrawler->pLeft;
		}
		else {
			if ( !traStk.empty() ){
				pCrawler = traStk.top();
				traStk.pop();
				cout <<  pCrawler->data << " ";
				pCrawler = pCrawler->pRight;
			} else {
				done = 1;
			}
		}
	}
	cout << endl;
}

void ZigZagTraversal(NodePtr pR){
	assert( pR != nullptr );

	NodePtr pCrawler = nullptr;

	std::stack<NodePtr> cL;
	std::stack<NodePtr> nL;
	cL.push(pR);

	bool dir = true;

	while ( !cL.empty() ){
		pCrawler = cL.top();
		cL.pop();

		cout << pCrawler->data << " ";
		if ( dir == true ){
			if ( pCrawler->pLeft )
				nL.push(pCrawler->pLeft);
			if ( pCrawler->pRight )
				nL.push(pCrawler->pRight);
		} else {
			if ( pCrawler->pRight )
				nL.push(pCrawler->pRight);
			if ( pCrawler->pLeft )
				nL.push(pCrawler->pLeft);
		}


		if ( cL.empty() ){
			dir = !dir;
			swap(cL, nL);
		}

	}
	cout << endl;
}

void LevleOrderTraversal(NodePtr pR){

	assert( pR != nullptr );

	NodePtr pCrawler = nullptr;

	std::queue<NodePtr> lQ;
	lQ.push(pR);

	while ( !lQ.empty() ){
		pCrawler = lQ.front();
		lQ.pop();
		cout << pCrawler->data << " ";

		if ( pCrawler->pLeft )
			lQ.push(pCrawler->pLeft);
		if ( pCrawler->pRight )
			lQ.push(pCrawler->pRight);
	}
	cout << endl;
}

NodePtr Balance(){
	
	if(ind  == 0){ return nullptr;  }

	int low = 0; 
	int high = ind;
	
	Release(_pRoot);
	rightHeight = leftHeight = 0;
	BalanceUtil(_pRoot,low,high);

	//Clear Balalnced Array and make ind 0// Imp for my logic not for the algo
	memset(balanced,0,sizeof(int)*ind);
	ind = 0;
	// ends 

	InOrder(_pRoot);
	level = 0;
	PrintBalancedTree();
	return nullptr;
}


int MinValue(NodePtr pR){
	return INT_MAX;
}

int MaxValue (NodePtr pR){
	return INT_MIN;
}

NodePtr SearchNode(NodePtr pR, int value){
	if ( pR == nullptr ){ return nullptr; }

	//Terminating Condition :
	if ( value == pR->data ){ cout << "Node Found" << endl; return pR; }

	NodePtr pFoundNode = nullptr;
	NodePtr pLeft = nullptr;
	NodePtr pRight = nullptr;
	pLeft = SearchNode(pR->pLeft, value);
	pRight = SearchNode(pR->pRight, value);

	if (pLeft!= nullptr){ 
		pFoundNode = pLeft; 
		if ( pFoundNode->pLeft == nullptr && pFoundNode->pRight == nullptr){
			cout << "InOrder Successor will be it's Parent" << endl;
		}
	}
	if ( pRight!= nullptr){ 
		pFoundNode = pRight; 
		if ( pFoundNode->pLeft == nullptr && pFoundNode->pRight == nullptr){
			cout << "InOrder Successor will be it's Parent's Parent(GrandParent" << endl;
		}
	}

	return pFoundNode;
}
NodePtr InOrderSuc(NodePtr pR,int value){
	//That's left most node of the right subtree...

	NodePtr pSourceNode = SearchNode(pR, value);

	cout << "Source Node Found!" << endl;
	if ( pSourceNode == nullptr && pSourceNode->pRight == nullptr ){ return nullptr; }
	cout << "Finding Successor Now!" << endl;

	NodePtr pC = pSourceNode->pRight;

	if ( pC == nullptr	){
		/*Special Case when there is nothing on the right and 
		Technical InOrderSuccessor is somewhere above the node 
		whose InOrder Successor we are finding*/
	} else {
		while ( pC->pLeft ){ pC = pC->pLeft; }
	}
	return pC;
}

NodePtr InOrderPred(NodePtr pR,int value){
	//That's the right most node of node's left subtree...
	return nullptr;
}

void Test_SampleInput(){

	int A[MAX_NODES] = { 0 };	

	int test_cases = 0;
	int size= 0;

	//cout << "Reading Sample Inputs" <<  endl;
	//freopen("BalancingTree_Sample_Input.txt", "r", stdin);
	cin >> test_cases;

	cout << "#TCs" << test_cases <<  endl;
	for (int tc = 0; tc < test_cases; tc++){
		cin >> size;
		for (int i = 0; i < size; i++){ 
			cin >> A[i]; 

			Insert(_pRoot, A[i]);
		}
		InOrder(_pRoot);
		level = 0;
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

	cout << "InOrder Traversal using Stack" << endl;
	InOrder_Stack(_pRoot);

	cout << "Level Order Traversal: " << endl;
	LevleOrderTraversal(_pRoot);

	cout << "ZigZag Order Traversal: " << endl;
	ZigZagTraversal(_pRoot);

	int nodeToFind = 0;
	cout << "Enter node to find:";
	cin >> nodeToFind;
	cout << "Find Node:[" <<nodeToFind << "]"<< endl;
	NodePtr find = SearchNode(_pRoot, nodeToFind);

	if ( find != nullptr ){
		cout << "Found Node:[" << find->data << "]" << endl; 
	} else {
		cout << "Node not found!" << endl; 
	}

	cout << "Enter node value for it's InOrder Successor: " ;
	cin >> nodeToFind;
	cout << "InOrder Success to Node:[" <<nodeToFind << "]"<< endl;
	find = InOrderSuc(_pRoot, nodeToFind);
	if ( find != nullptr ){
		cout << "InOrder Successor :[" << find->data << "]" << endl; 
	} else {
		cout << "InOrder Successor not found!" << endl; 
	}

	Release(_pRoot);
}
void Test_RandomisedDataInput(){

	int A[MAX_NODES] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(nullptr));
	size = rand() % 20;
	srand(time(nullptr));

	for (int i = 0; i< size; i++){
		int value = rand() % MAX_NODES;
		A[i] = value;

		cout << "Random Node:["<< value <<"]" << endl;
		Insert(_pRoot,value);
	}
	InOrder(_pRoot) ;
	level= 0;
	PrintBalancedTree();
	Balance();
	PrintBalancedTree();
	cout << "PreOrder:" << endl;
	PreOrder(_pRoot);
	cout << endl;
	cout << "PostOrder:" << endl;
	PostOrder(_pRoot);
	cout << endl;

	cout << "InOrder Traversal using Stack" << endl;
	InOrder_Stack(_pRoot);

	cout << "Level Order Traversal: " << endl;
	LevleOrderTraversal(_pRoot);

	cout << "ZigZag Order Traversal: " << endl;
	ZigZagTraversal(_pRoot);

	int nodeToFind = 0;
	cout << "Enter node to find: " ;
	cin >> nodeToFind;
	cout << "Find Node:[" <<nodeToFind << "]"<< endl;
	NodePtr find = SearchNode(_pRoot, nodeToFind);

	if ( find != nullptr ){
		cout << "Found Node:[" << find->data << "]" << endl; 
	} else {
		cout << "Node not found!" << endl; 
	}

	cout << "Enter node value for it's InOrder Successor: " ;
	cin >> nodeToFind;
	cout << "InOrder Success to Node:[" <<nodeToFind << "]"<< endl;
	find = InOrderSuc(_pRoot, nodeToFind);
	if ( find != nullptr ){
		cout << "InOrder Successor :[" << find->data << "]" << endl; 
	} else {
		cout << "InOrder Successor not found!" << endl; 
	}

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
