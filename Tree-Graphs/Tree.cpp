#include "Tree.h"
#include <ctime>
#include <chrono>

using namespace std;

int ar[MAX_NODES] ={0};
//int balanced[MAX_NODES] ={0};

NodePtr  _pRoot = nullptr;
std::vector<int> orderVector;

NodePtr CreateNode(int value){
	NodePtr pTemp = new TNode();
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

void FillNodeVector(NodePtr pR, vector<NodePtr>& v){
	
	if( pR == nullptr){ return;  }
	FillNodeVector(pR->pLeft, v);	
	v.push_back(pR);
	FillNodeVector(pR->pRight, v);
}
void TreeNodeStats(NodePtr pR){

	vector<NodePtr> nodeVector;
	std::vector<NodePtr>::iterator ite;
	FillNodeVector(pR, nodeVector);

	cout << "*************Balance Stats*************" << endl;
	for(ite = nodeVector.begin(); ite != nodeVector.end(); ++ite){
		NodePtr pC = *ite;
		cout << pC->data <<"-"<< pC->lC << "-"<<pC->rC << "-" << pC->height <<endl;
	}
	cout << "***************************************" << endl;

}

NodePtr Insert(NodePtr pR,int value){

	if( pR == nullptr){  
		pR = CreateNode(value); 
		return pR; 
	}
	
	if( value < pR->data ){
		pR->lC += 1;

		if( pR->pLeft != nullptr){
			pR->pLeft->height = pR->height+1;   
			Insert(pR->pLeft,value); 
		}
		else { pR->pLeft = CreateNode(value); }
	} else {
		pR->rC += 1;

		if( pR->pRight != nullptr){ 
			pR->pRight->height = pR->height+1;   
			Insert(pR->pRight,value);
		}
		else { pR->pRight= CreateNode(value); }
	}
	
	return pR;
}

void InOrder(NodePtr pR, vector<int>* order /*=nullptr*/){

	if( pR == nullptr){ return;  }
	InOrder(pR->pLeft);
	//cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC << "-" << pR->height <<endl;
	#ifdef __PRINT_TRAVERSALS__ 
		cout <<  pR->data << " ";
	#else 
		order->push_back(pR->data);
	#endif
	//cout << pR->data <<" " ;
	InOrder(pR->pRight);
}

void PreOrder(NodePtr pR, vector<int>* order /*=nullptr*/){
	if( pR == nullptr){ return;  }
	#ifdef __PRINT_TRAVERSALS__ 
		cout <<  pR->data << " ";
	#else 
		order->push_back(pR->data);
	#endif
	PreOrder(pR->pLeft);
	//cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC <<endl;
	PreOrder(pR->pRight);	
}

void PostOrder(NodePtr pR, vector<int>* order /*=nullptr*/){
	if( pR == nullptr){ return;  }
	PostOrder(pR->pLeft);
	//cout << pR->data <<"-"<< pR->lC << "-"<<pR->rC <<endl;
	PostOrder(pR->pRight);
	#ifdef __PRINT_TRAVERSALS__
		cout <<  pR->data << " ";
	#else 
		order->push_back(pR->data);
	#endif
}

NodePtr BalanceUtil(NodePtr pR, NodeDPtr pNewHead, int low,int high, vector<NodePtr>& v){
	
	if(low >= high){ return nullptr;  }
	int mid = (low + high) /2;

	//cout << "Bal Inserting:[" << balanced[mid] <<"]" << endl;
	NodePtr pTemp = v[mid];
	//cout << "V[mid]:[" << pTemp->data << "]" << endl;
	if( pTemp != nullptr)
		*pNewHead = Insert(*pNewHead,pTemp->data);

	BalanceUtil(pR,pNewHead, low,mid, v);
	BalanceUtil(pR,pNewHead, mid+1,high, v);
	return *pNewHead;
}

NodePtr Balance(NodePtr pR){
	
	if (pR == nullptr) { cout << "Tree is empty!" << endl; return nullptr; }

	std::vector<NodePtr> nodeVector;
	FillNodeVector(pR, nodeVector);
	
	int low = 0; 
	int high = nodeVector.size();

	NodePtr pNewHead = nullptr;
	pNewHead = BalanceUtil(_pRoot,&pNewHead, low,high, nodeVector);
	Release(_pRoot);
	_pRoot = pNewHead;
	return pNewHead;
}

void InOrder_Stack(NodePtr pR, vector<int>* order /*=nullptr*/){

	std::time_t before = std::time(nullptr);

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
				#ifdef __PRINT_TRAVERSALS__ 
				cout <<  pCrawler->data << " ";
				#else 
					order->push_back(pCrawler->data);
				#endif
				pCrawler = pCrawler->pRight;
			} else {
				done = 1;
			}
		}
	}
	std::time_t after  = std::time(nullptr);
	cout << endl;
	auto diff = (after - before) ;
	/*std::chrono::milliseconds ms = (std::chrono::milliseconds)diff;
	std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds> (ms);   // truncated*/
	cout  << "InOrder Time Diff :[" <<  diff << "] " <<endl;
	cout  << "Calculated using diffTime :[" <<  std::difftime(after, before) << "] secs. " <<endl;
}

void ZigZagTraversal(NodePtr pR,  vector<int>* order /*=nullptr*/){
	assert( pR != nullptr );

	NodePtr pCrawler = nullptr;

	std::stack<NodePtr> cL;
	std::stack<NodePtr> nL;
	cL.push(pR);

	bool dir = true;

	while ( !cL.empty() ){
		pCrawler = cL.top();
		cL.pop();

		#ifdef __PRINT_TRAVERSALS__ 
			cout <<  pCrawler->data << " ";
		#else 
			order->push_back(pCrawler->data);
		#endif
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
	#ifdef __PRINT_TRAVERSALS__ 
		cout << endl;
	#endif
}

void LevleOrderTraversal(NodePtr pR, vector<int>* order /*=nullptr*/){

	assert( pR != nullptr );

	NodePtr pCrawler = nullptr;

	std::queue<NodePtr> lQ;
	lQ.push(pR);

	while ( !lQ.empty() ){
		pCrawler = lQ.front();
		lQ.pop();
		#ifdef __PRINT_TRAVERSALS__ 
			cout <<  pCrawler->data << " ";
		#else 
			order->push_back(pCrawler->data);
		#endif

		if ( pCrawler->pLeft )
			lQ.push(pCrawler->pLeft);
		if ( pCrawler->pRight )
			lQ.push(pCrawler->pRight);
	}
	cout << endl;
}


NodePtr MinValue(NodePtr pR){
	assert ( pR != nullptr );
	while ( pR->pLeft != nullptr ){ pR = pR->pLeft; }
	return pR;
}

NodePtr MaxValue (NodePtr pR){
	assert ( pR != nullptr );
	while ( pR->pRight != nullptr ){ pR = pR->pRight; }
	return pR;
}

NodePtr SearchNode(NodePtr pR, int value){
	if ( pR == nullptr ){ return nullptr; }

	//Terminating Condition :
	if ( value == pR->data ){ cout << "Node Found" << endl; return pR; }

	NodePtr pFoundNode = nullptr;
	NodePtr pLeft = nullptr;
	NodePtr pRight = nullptr;

	pLeft = SearchNode(pR->pLeft, value);
	if( pLeft == nullptr ){
		pRight = SearchNode(pR->pRight, value);
	}

	if ( pLeft!= nullptr){  pFoundNode = pLeft; }
	if ( pRight!= nullptr){  pFoundNode = pRight; }

	return pFoundNode;
}

NodePtr InOrderSuc(NodePtr pR,int value){

	//NodePtr pC = pR;	
	//assert( pR != nullptr);
	if ( pR == nullptr ){ cout << "Root is null" << endl; return nullptr; }
	NodePtr pSource = SearchNode(pR, value);
	NodePtr pSucc = nullptr;

	if ( pSource == nullptr ){ cout << "Search node not found!" << endl; return nullptr; }

	if ( pSource->pRight ){ 
		pSucc = MinValue(pSource->pRight);
		return pSucc;
	}
	
	while ( 1 ){
		if ( pSource->data < pR->data ){
			pSucc = pR;
			pR = pR->pLeft;
		} 
		else if ( pSource->data > pR->data ){
			pR = pR->pRight;
		}
		else {
			return pSucc;
		}
	}
	return nullptr;
}

NodePtr InOrderPred(NodePtr pR,int value){
	//That's the right most node of node's left subtree...
	return nullptr;
}

void WriteToFile( const std::string& inputString, vector<int> keys){
	std::ofstream ofs;
	ofs.open ( __TREE_FILE_NAME__, std::ofstream::out | std::ofstream::app);
	cout << "Writing to Trie Directory:[" << __TREE_FILE_NAME__ << "]" << endl;

	if (ofs.is_open()){
		ofs << inputString << endl;
		vector<int>::iterator ite;
		for ( ite = keys.begin(); ite!=keys.end(); ++ite){
			ofs << *ite <<" ";
		}
	} else {
		cout << "Error in opening/writing to directory file" << endl;
	}
	ofs.close();
}

NodePtr LCA(NodePtr pRoot, int left, int right){
	
	if (pRoot == NULL){  return nullptr; }
	if (pRoot->data == right || pRoot->data == left){  return pRoot; }

	NodePtr l = LCA(pRoot->pLeft, left, right);
	NodePtr r = LCA(pRoot->pRight, left, right);

	if ( l && r){  return pRoot }
	return (l != nullptr ? l : r);
}

void DeepestLeaves(NodePtr pRoot, stack<int>& dl){

	if ( pRoot == nullptr){ return;}
	if ( pRoot->pLeft == nullptr && pRoot->pRight == nullptr){
		cout << "Deepest Node:[" << pRoot->data << "]" << endl;
		dl.push(pRoot->data);
		return;
	}

	DeepestLeaves(pRoot->pLeft, dl);
	DeepestLeaves(pRoot->pRight, dl);
	return;
}

/*
void PrintTree(){
	#ifdef __PRINT_TRAVERSALS__ 
		cout << "Balanced BST" << endl;
		for(int i = 0; i< ind; i++){
			cout << balanced[i] << " ";
		}
		cout << endl;
	#endif
}

*/
