#include <iostream.h>

#define MAX_SIZE 26


class AccessVTable
{
public:
	virtual void fnCallVTableFunc()
	{
		cout<<"fnCallVTableFunc Called...";
	}
	virtual void fnDisplay()
	{
		cout<<"fnDisplay Called...";
	}
	virtual void fnTest()
	{
		cout<<"fnTest Called...";
	}
};
class DeriveAccessVTable
{
public:
};
class Abstract
{
	static int iPrivateStatic;
public:
	virtual void fnDisplay()=0
	{
		cout<<"Abstract's display"<<endl;
	}
	Abstract()
	{
		cout<<"\nAbstract Class Contructor\n";
	}
	virtual ~Abstract()=0;
};
class Base :public Abstract
{
public:
  virtual int f() { return 1; }
  void fnDisplay()
  {
	  Abstract::fnDisplay();
	  cout<<"Base's function"<<endl;
  }
};

class Derived : public Base
{
public:
  int f() 
  { 
	  return 2; 
  }
  void fnDisplay()
  {
	  Base::fnDisplay();
	  cout<<"Derived's display"<<endl;
  }
};

//To restrict object creation on stack : Make destructor of a class private, which will allow object creation on heap but not on stack.
class Temp
{
public:
	~Temp()
	{
		cout<<"Temp : Destructor called!"<<endl;
	}
	Temp()
	{
		cout<<"Temp : Constrcutor with no argument called!"<<endl;
	}
	Temp(Temp& t)
	{
		cout<<"Temp : Constructor with 1 argument of itself(value) called"<<endl;
	}
	Temp(int iValue)
	{
		cout<<"Temp : Constructor with 1 int argument called"<<endl;
	}
	Temp(Temp* clpCopy)
	{
		cout<<"Temp : Constructor with 1 argument of itself(Pointer) called"<<endl;
	}
	int iInt;
};
//To restrict object creatio on Heap, do following : Override new and delepe operators of a class and keep them in private section.


struct TreeNode
{
	int			data;
	TreeNode	*pLeft;
	TreeNode	*pRight;
};
bool InsertTreeNode( TreeNode **ppRootNode, int Value);
bool DeleteTreeNode( TreeNode *pRootNode, int Value);
bool SearchTreeNode( TreeNode *pRootNode, int Value);
bool ReleaseTreeNodes( TreeNode** ppRootNode );
bool	TraverseTree_InOrder(TreeNode* pRootNode);
bool	TraverseTree_PreOrder(TreeNode* pRootNode);
bool	TraverseTree_PostOrder(TreeNode* pRootNode);

bool CreateMirrorImageTree(TreeNode **ppRootNode, int Value, int iDir);
bool MirrorImage(TreeNode* pRootNode, TreeNode* pLeft, TreeNode* pRight);

//Search methods...
bool	DFS(TreeNode *pRootNode);
bool	BFS(TreeNode *pRootNode);


//Implementatio of Trie tree
//data structure for trie
struct TrieTreeNode
{
	int				iIndex;
	char			charValue;
	TrieTreeNode*	pChild[MAX_SIZE];
	bool			bEndOfWord;
	TrieTreeNode();
	~TrieTreeNode();
};

bool	InsertValue(TrieTreeNode*	pHead,char*		pInput);
void	FindWord(TrieTreeNode*	pHead,char*		pInput);
void	FindWordByPrefix(TrieTreeNode*	pHead,char*		pInput);
void	FreeTrieTree(TrieTreeNode*		pHead);
void	ExtractWordFromNode(TrieTreeNode*		pHead);
