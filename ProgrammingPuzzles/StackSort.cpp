#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <time.h>
#include <stdlib.h>

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

bool SortStack(stack<int> orgStk){

	if ( orgStk.empty()){ return false; }
	cout<<"Sorting Stack"<<endl;

	int PN=-1;
	stack<int> auxiStk;

	while ( orgStk.empty() == false){
		PN = orgStk.top();
		orgStk.pop();
		if( auxiStk.empty()){
			auxiStk.push(PN);
		} else {
			if ( PN <=auxiStk.top()){
				auxiStk.push(PN);
			} else {
				while (auxiStk.empty() == false && PN > auxiStk.top() ){
					int temp = auxiStk.top();
					auxiStk.pop();
					orgStk.push(temp);
				}
				auxiStk.push(PN);
			}
		}
		PrintStack(auxiStk);
	}
	return false;
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
		SortStack(sortStack);
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
	SortStack(sortStack);
#endif
	
	return 0;
}