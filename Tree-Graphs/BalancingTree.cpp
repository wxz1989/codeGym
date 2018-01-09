#include <bits/stdc++.h>
#include "Tree.h"

using namespace std;

extern NodePtr  _pRoot;

void Test_SampleInput(){

	//int A[MAX_NODES] = { 0 };	

	int test_cases = 0;
	int size= 0;

	//cout << "Reading Sample Inputs" <<  endl;
	//freopen("BalancingTree_Sample_Input.txt", "r", stdin);
	cin >> test_cases;

	cout << "#TCs" << test_cases <<  endl;
	for (int tc = 0; tc < test_cases; tc++){
		cin >> size;
		int value = 0;
		for (int i = 0; i < size; i++){ 
			//cin >> A[i]; 
			cin >> value;

			_pRoot = Insert(_pRoot, value);
		}

		cout << "InOrder:" << endl;
		InOrder(_pRoot);
		cout << endl;
		TreeNodeStats(_pRoot);
	}
	_pRoot = Balance(_pRoot);
	TreeNodeStats(_pRoot);

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

	//int A[MAX_NODES] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(nullptr));
	size = rand() % MAX_NODES;
	srand(time(nullptr));

	for (int i = 0; i< size; i++){
		int value = rand() % MAX_NODES;
		//A[i] = value;
		#if 0
		cout << "Random Node:["<< value <<"]" << endl;
		#endif
		_pRoot = Insert(_pRoot,value);
	}
	InOrder(_pRoot) ;
	TreeNodeStats(_pRoot);
	Balance(_pRoot);
	TreeNodeStats(_pRoot);
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

	NodePtr pMin = MinValue(_pRoot);
	cout << "Find Min Node:[" <<  pMin->data << "]" << endl;

	NodePtr pMax = MaxValue(_pRoot);
	cout << "Find Max Node:[" <<  pMax->data << "]" << endl;

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
