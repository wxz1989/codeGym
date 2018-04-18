#ifndef __TREE_H__
#define __TREE_H__

#ifndef __PRINT_TRAVERSALS__
#define __PRINT_TRAVERSALS__
#endif

/*#ifdef __PRINT_TRAVERSALS__
#undef __PRINT_TRAVERSALS__
#endif*/

//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <assert.h>
#include <fstream>

#define MAX_NODES /*100*/ 10
#define __TREE_FILE_NAME__  ".bst_keys_directory.txt"

struct _tree_node_;
typedef struct _tree_node_ 		TNode;

struct _tree_node_{
	int data;
	int height;
	int rC, lC;			//For Maintaining the Balance Factor of the Tree, lC=>left children count of the node, rC=>right children count of the node
	TNode* pLeft,*pRight;
};

typedef struct _tree_node_* 	NodePtr;
typedef struct _tree_node_** 	NodeDPtr;

extern NodePtr  _pRoot ;
//All Open APIs for Trees

// NODE CREATING FACTORY METHOD
NodePtr CreateNode(int value);

//INSERT RECURSIVE BST PROPERTIES MAINTAINIED AND RETURNS PTR TO ROOT NODE
NodePtr Insert(NodePtr pR,int value);

//DELETE FRMO BST
NodePtr Delete(NodePtr pR, int value);

// SEARCHING IN BST
NodePtr SearchNode(NodePtr pR, int value);

//TRAVERSALS
//ITERATIVE
void InOrder_Stack(NodePtr pR , std::vector<int>* order=nullptr);

//RECURSIVE
void InOrder(NodePtr pR, std::vector<int>* order=nullptr);
void PreOrder(NodePtr pR, std::vector<int>* order=nullptr);
void PostOrder(NodePtr pR, std::vector<int>* order=nullptr);

//SPECIAL TRAVERSALS 
void ZigZagTraversal(NodePtr pR, std::vector<int>* order=nullptr);
void LevleOrderTraversal(NodePtr pR, std::vector<int>* order=nullptr);

//TREE BALANCING: USES INORDER TRAVERSAL OF A TREE 
NodePtr Balance(NodePtr pR);
NodePtr BalanceUtil(NodePtr pR, NodeDPtr pNewHead, int low,int high, std::vector<NodePtr>& v);

NodePtr MinValue(NodePtr pR);
NodePtr MaxValue (NodePtr pR);

//INORDER SUCCESSOR AND PREDECESSOR
NodePtr InOrderSuc(NodePtr pR,int value);
NodePtr InOrderPred(NodePtr pR,int value);

//UTILITY  : CURRENTLY USES GLOBAL ARRAY TO ITERATE AND PRINT, CAN BE CHANGED TO VECTOR OR ARRAY LIST
//void PrintTree();

//RECURSIVE DELETE / FREES BST AND RELEASES NODES. (TEST IS USING VALGRIND)
void ReleaseUtil(NodePtr pR);
void Release(NodePtr pR);

void TreeNodeStats(NodePtr pR);
//Writing content to directory
void WriteToFile(const std::string& inputString, int keys);
void DeepestLeaves(NodePtr pRoot, std::stack<int>& dl);
NodePtr LCA(NodePtr pRoot, int left, int right);

#endif 		/*__TREE_H__*/
