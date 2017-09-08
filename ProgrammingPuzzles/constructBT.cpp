#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#define MAX_ARRAY_SIZE 100

using namespace std;

void Test_SampleInput();
void Test_RandomisedDataInput();
int Solve();


int Solve(){
	return 0;
}

/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


//Structure of the Node of the binary tree is as
struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
};


typedef struct Node Node;
typedef struct Node* NodePtr;
typedef struct Node** NodeDPtr;

NodePtr CreateNewNode(int nodeValue){
	NodePtr pNewNode = new Node();
	//cout << "New Node with value :[" << nodeValue << "]" << endl;
	if ( pNewNode  != nullptr){
		pNewNode->data = nodeValue;
		pNewNode->left = nullptr;
		pNewNode->right = nullptr;
		return pNewNode;
	}
	return nullptr;
}

/* Given a binary tree, print its nodes in inorder*/
void printInorder(NodePtr node)
{
     if (node == nullptr)
          return;
 
     /* first recur on left child */
     printInorder(node->left);
 
     /* then print the data of node */
     printf("%d ", node->data);  
 
     /* now recur on right child */
     printInorder(node->right);
}


// function should return the root of the new binary tree formed
struct Node *constructTree(int n, int pre[], char preLN[])
{
	if( n <=0 )	{ return nullptr; }

	NodePtr pRootToReturn = nullptr;
	vector<NodePtr> nodeVector;
	//Insert first Node of the stream as that's the root of the stream and has to be in Vector before processing all other nodes.
	NodePtr pNewNode = CreateNewNode(pre[0]);
	NodePtr pRoot;
	pRootToReturn = pNewNode;
	nodeVector.push_back(pNewNode);

	int pi = nodeVector.size() - 1, ci = 1;

	for ( int i = ci; i < n ; i++,  ci++){

		pi = nodeVector.size() - 1;
		if( preLN[i] ==  'N'){
			pRoot = nodeVector[pi];
			pNewNode = CreateNewNode(pre[ci]);
			nodeVector.push_back(pNewNode);
			
			//cout << "Current Root:[" << pRoot->data <<"]" << endl;

			if ( pRoot->left == nullptr){
				pRoot->left = pNewNode;
			} else if ( pRoot->right == nullptr){
				pRoot->right = pNewNode;
				/*Following line makes so much difference, 
				as current parent node has been inserted with a Right Node 
				and now that parent could not hold any more childs, 
				it should have been removed. 
				So nodeVector keeps consistent data and 
				keeps only those nodes which are potential parents.*/
				nodeVector.erase(nodeVector.begin() + pi);
			}
		} else {
			pNewNode = CreateNewNode(pre[ci]);
			/* Issue#1 : Fixed this issue, as those nodes which are already marked as Leaves, 
			need not be added in the nodeVector. Purpose of nodeVector is,
			to hold only those nodes which are potential parents.
			*/
			//nodeVector.push_back(pNewNode);
			pRoot = nodeVector[pi];

			//cout << "Current Root:[" << pRoot->data <<"]" << endl;

			if ( pRoot->left == nullptr){
				pRoot->left = pNewNode;
			} else if ( pRoot->right == nullptr){
				pRoot->right = pNewNode;
				nodeVector.pop_back();
			}
		}
	}
	return pRootToReturn;
}

void Test_SampleInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };	
	char aLN[MAX_ARRAY_SIZE] = { 0 };	

	int test_cases = 0;
	int size= 0;

	//cout << "Reading Sample Inputs" <<  endl;
	freopen("ConstructBinTree.txt", "r", stdin);
	cin >> test_cases;

	cout << "#TCs" << test_cases <<  endl;
	for (int tc = 0; tc < test_cases; tc++){

		cin >> size;
		cout << "#Size:" << size <<  endl;

		for (int i = 0; i < size; i++){
			cin >> A[i];
			//cout << A[i] <<" ";
		}
		//cout << endl;
		for (int i = 0; i < size; i++){
			cin >> aLN[i];
			//cout << aLN[i] <<" ";
		}
		//cout << endl;


		//int Ans = Solve();
		struct Node* pRootNode = constructTree(size, A, aLN);
		//cout << "Verifying using InOrder Traversal" << endl;
		printInorder(pRootNode);
		cout<< endl;
		//cout << "# " << tc<< "[" <<pRootNode->data <<"]" <<  endl;

		for ( int i = 0; i< MAX_ARRAY_SIZE; i++){
			A[i] = 0;
			aLN[i] = '\0';
		}
	}
}
void Test_RandomisedDataInput(){

	int A[MAX_ARRAY_SIZE] = { 0 };

	int test_cases = 0;
	int size = 0;

	srand(time(nullptr));
	size = rand() % 10;
	srand(time(nullptr));

	for (int i = 0; i< size; i++){
		int value = rand() % 30;
		A[i] = value;
	}
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
