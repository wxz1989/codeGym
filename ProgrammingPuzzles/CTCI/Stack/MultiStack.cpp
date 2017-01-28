#include <iostream>
#include <stdio.h>
#include <stack>

using namespace std;

#define STACK_CAPACITY 10
#define MIN_VALUE  999999999

int minValue = MIN_VALUE;

stack<stack<int>*> mMultiStack;
stack<int> minStack;

stack<int>* pCurrentStack = NULL;
//For having a dynamically growing Master Stack List, I can use
// 1. Stack
// 2. LinkedList
// 3. ArrayList(Easy Implementation) for index based data retrival
// 4. ArrayOnly


int GetMinValue(){
	if (!minStack.empty()){
		return minStack.top();
	}
	return MIN_VALUE;
}

void PrintStack(){
	cout << "Multi Stack Content:" << endl;
	while( !mMultiStack.empty() ){
		stack<int>* pTempStack = NULL;
		pTempStack = mMultiStack.top();
		mMultiStack.pop();

		cout << "Stack[" << stackCount-- << "]: ";
		while(!pTempStack->empty()){
			cout << pTempStack->top() << " " ;
			pTempStack->pop();
		}
		cout <<endl;
	}
}

void Reset(){
	while( !mMultiStack.empty() ){
		stack<int>* pTempStack = NULL;
		pTempStack = mMultiStack.top();
		mMultiStack.pop();

		while(!pTempStack->empty()){
			 pTempStack->pop();
		}
		delete pTempStack;
	}
}

int CreateNewStack(){
	stack<int>* pTemp = new stack<int>;
	pCurrentStack = pTemp;
	mMultiStack.push(pCurrentStack);
	stackCount++;
	return 1;
}

int Init(){
	if( mMultiStack.empty()){
		pCurrentStack = new stack<int>;
		mMultiStack.push(pCurrentStack);

		stackCount++;
		return 1;
	}
	return 0;
}

stack<int>* GetCurrentStackPtr(){
	return pCurrentStack;
}

int  Top(){
	int returnValue = 0;
	stack<int>* pTempStack =  GetCurrentStackPtr();
	if ( pTempStack == NULL ){ cout << "Stack is already empty!" << endl ; return -1; 	}

	if ( mMultiStack.empty() ){
		cout << "Stack is empty!" << endl;
	} else {
		returnValue = pTempStack->top();
	}
	return returnValue;
}

void Pop(){
	stack<int>* pTempStack =  GetCurrentStackPtr();
	if ( pTempStack == NULL ){ cout << "Stack is already empty!" << endl ; return; 	}

	if ( mMultiStack.empty() ){
		cout << "Stack is empty!" << endl;
	} else {
		int value = pTempStack->top();

		if ( value == GetMinValue()){
			minStack.pop();
		}

		pTempStack->pop();

		if ( pTempStack->empty()){
			delete pTempStack;
			pCurrentStack = NULL;

			if (mMultiStack.size() == 1 ){
				mMultiStack.pop();
			} else {
				mMultiStack.pop();
				pCurrentStack = mMultiStack.top();
			}
		} 
	}
	return;
}

void Push(int value){
	stack<int>* pTempStack = NULL;

	if ( mMultiStack.empty() ){
		if ( !Init() ){
			cout << "Stack Allocation failed" << endl;
			return;
		} 
		pTempStack = GetCurrentStackPtr();
		pTempStack->push(value);
	} else {
		pTempStack = GetCurrentStackPtr();
		pTempStack->push(value);

		if ( pTempStack.size() == STACK_CAPACITY ){
			if ( !CreateNewStack() ){
				cout << "Stack Rellocation failed"<< endl;
			}
		}
	}

	if(value < minValue){
		minValue = value;
		minStack.push(value);
	}
}

int main(int argc, char* argv[]){
	
	int test_cases = 0;

	int totalStackSize =0;
	freopen("MultiStack_Sample_Input.txt", "r", stdin);

	int stackSize = 0;
	cin >> test_cases;
	cout << "Test cases:"<<test_cases << endl;

	for (int tc = 0; tc < test_cases; tc++){
		cin >> stackSize;

		totalStackSize += stackSize;

		cout << "Stack Size:"<<stackSize << endl; 
		for (int i = 0; i < stackSize; i++){
			int value = 0;
			cin >>value;
			Push(value);
		}
	}
	//PrintStack();

	//Read untill all elements are read from stack.
	cout << "Total Stack Size:" << totalStackSize << endl;
	for ( int i = 0; i< totalStackSize;i++){
		cout << "Top=>(" << i+1 <<") "<<  Top() << "   MinValue:("<< GetMinValue() <<")" << endl;
		Pop();
	}
	Reset();

	return 0;
}