#ifndef __BT_H__
#define __BT_H__

struct TreeNode
{
	int			data;
	TreeNode	*pLeft;
	TreeNode	*pRight;
};


typedef TreeNode* TreeNodePtr;
typedef TreeNode** TreeNodeDPtr;

TreeNodePtr __pRoot = nullptr;

bool InsertTreeNode( TreeNode **ppRootNode, int Value);
bool DeleteTreeNode( TreeNode *pRootNode, int Value);
bool SearchTreeNode( TreeNode *pRootNode, int Value);
bool ReleaseTreeNodes( TreeNode** ppRootNode );
bool	TraverseTree_InOrder(TreeNode* pRootNode);
bool	TraverseTree_PreOrder(TreeNode* pRootNode);
bool	TraverseTree_PostOrder(TreeNode* pRootNode);

bool CreateMirrorImageTree(TreeNode **ppRootNode, int Value, int iDir);
bool MirrorImage(TreeNode* pRootNode, TreeNode* pLeft, TreeNode* pRight);


#endif /*__BT_H__*/
