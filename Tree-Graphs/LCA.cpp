#include<iostream>
#include <conio.h>
using namespace std;

#define MIN_NODES 3
#define MAX_NODES 10000

int V = 0, E = 0, l = 0, r = 0;

struct TreeNode{
	int value;
	int left;
	int right;

	int lChildCount;
	int rChildCount;

	TreeNode(){
		value =-1;
		left = -1;
		right = -1;
		lChildCount = 0;
		rChildCount = 0;
	}
};

typedef struct TreeNode TNodeA;
TNodeA tree[MAX_NODES];
TNodeA root;


void Reset(){
	for (int i = 0; i< MAX_NODES; i++){
		tree[i].value = -1;
		tree[i].lChildCount = 0;
		tree[i].rChildCount = 0;
		tree[i].left = -1;
		tree[i].right = -1;
	}
	V = -1;
	E = -1;
	l = -1;
	r = -1;
	root.value = -1;
}

void buildTreeFromArray();
bool findLCAFromTreeArray(int root, int left, int right, int& lca);
int ChildCount(int root, int& child);


int ChildCount(int root, int& child){
	if (root < 1 || root > MAX_NODES){  --child;   return 0;  }
	ChildCount(tree[root].left, ++child);
	ChildCount(tree[root].right, ++child);
	return child;
}

void buildTreeFromArray(){

	bool rootSet = false;
	int source = -1;
	int dest = -1;

	for (int i = 0; i < E; i++){
		cin >> source;
		cin >> dest;

		if (rootSet == false){
			root.value = source;	
			rootSet = true;
		}
		tree[source].value = source;
		tree[dest].value = dest;

		if (tree[source].left == -1)
			tree[source].left = dest;
		else {
			tree[source].right = dest;
		}
	}
}

bool findLCAFromTreeArray(int root, int left, int right, int& lca){

	bool bLeft = false, bRight = false;
	if (root < 1 || root > MAX_NODES){ return false; }

	if (tree[root].value == left){ return true; }
	if (tree[root].value == right ){ return true; }

	bLeft = findLCAFromTreeArray(tree[root].left, left, right, lca);
	bRight = findLCAFromTreeArray(tree[root].right, left, right, lca);

	if (bLeft && bRight){ lca = tree[root].value;  }
	return (bLeft == true ? bLeft : bRight);
}



int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	The freopen function below opens input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);
	cin >> T;

	/*
	Read each test case from standard input.
	*/

	Reset();

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> V;
		cin >> E;
		cin >> l;
		cin >> r;

		buildTreeFromArray();
		
		int lca = -1;
		if ( root.value == l || 
			 root.value == r) { 
			cout << "#" << test_case << " -1" << endl;
		} else {
			if (findLCAFromTreeArray(root.value, l, r, lca)){
				int children = 0;
				ChildCount(lca, children);
				cout << "#" << test_case << " " << lca << " " << children + 1 << endl;
			}
			else {
				cout << "#" << test_case << " -1" << endl;
			}
		}
		Reset();
	}
	_getche();
	return 0;//Your program should return 0 on normal termination.
}
