#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef READ_DATA_FROM_FILE
#define READ_DATA_FROM_FILE
#endif

std::stack<int> sortStack;

void Reset(){
	while (!sortStack.empty()){
		sortStack.pop();
	}
}

using namespace std;

void PrintStack(stack<int> orgStk){

	if ( orgStk.empty()){ return; }
	cout <<"Stack["<<orgStk.size()<<"]:[";

	while(!orgStk.empty()){
		cout << orgStk.top() <<" ";
		orgStk.pop();
	}
	cout <<"]"<<endl;
}
//Time Complexity = O(N^2)
//Space Complexity = O(N). 
//A new Auxiliary stack auxiStk, is taken for storying elements before writing it back to original Stack 
bool SortStack(stack<int> orgStk){

	if ( orgStk.empty()){ return false; }
	cout<<"Sorting Stack"<<endl;

	int PN=-1;
	stack<int> auxiStk;

	while ( orgStk.empty() == false){
		PN = orgStk.top();
		orgStk.pop();
		
		while (auxiStk.empty() == false && PN > auxiStk.top() ){
			int temp = auxiStk.top();
			auxiStk.pop();
			orgStk.push(temp);
		}
		auxiStk.push(PN);
	}
	PrintStack(auxiStk);
	return false;
}

void InsertIntoStack(std::stack<int>& stk, int Value){
	//cout << "InsertIntoStack:[" << Value << "]" << endl;
	if( stk.empty() || Value > stk.top() ){
		stk.push(Value);
	} else{
		int top = stk.top();
		stk.pop();
		InsertIntoStack(stk, Value);
		stk.push(top);
	}
	return;
}

void SortStackRec(std::stack<int>& orgStk){
	
	if( !orgStk.empty() ){
		int top = orgStk.top();
		orgStk.pop();
		SortStackRec(orgStk);
		
		//cout << "Inserting:[" << top << "]" << endl;
		InsertIntoStack(orgStk, top);
		//PrintStack(orgStk);
	}
	return;
}

int main ()
{
	int test_cases = 0;
	
	int sizeOfStack = 0;

#ifdef READ_DATA_FROM_FILE
	cout << "Reading from File"<<endl;

	freopen("SortStack_Sample_Input.txt", "r", stdin);
	cin >> test_cases;

	for ( int tc = 0; tc< test_cases;tc++){
		cin >> sizeOfStack;
		
		for ( int i = 0; i< sizeOfStack;i++){
			int value=0;
			cin >> value;
			sortStack.push(value);	
		}	
		cout<<"Original Stack:"<<endl;
		PrintStack(sortStack);
		//SortStack(sortStack)
		cout<<"Sorted Stack:"<<endl;;
		SortStackRec(sortStack);
		PrintStack(sortStack)	;
		Reset();
	}
#else
	std::stack<int> mystack;
	srand(time(NULL));
	sizeOfStack = rand()%10;
	srand(time(NULL));
	for ( int i = 0; i< sizeOfStack;i++){
		sortStack.push(rand()%10);
	}
	cout<<"Original Stack:"<<endl;
	PrintStack(sortStack);
	SortStackRec(sortStack);
	PrintStack(sortStack);
#endif
	
	return 0;
}
