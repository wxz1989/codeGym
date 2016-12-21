#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <time.h>
#include <stdlib.h>

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
	std::stack<int> mystack;

	srand(time(NULL));
	int sizeOfStack = rand()%10;
	srand(time(NULL));
	for ( int i = 0; i< sizeOfStack;i++){
		mystack.push(rand()%10);
	}

	/* Sample Input, asked during interview
	mystack.push(5);
	mystack.push(2);
	mystack.push(1);
	mystack.push(9);
	mystack.push(7);
	//

	mystack.push(5);
	mystack.push(4);
	mystack.push(3);
	mystack.push(2);
	mystack.push(1);
	*/

	cout<<"Original Stack:"<<endl;
	PrintStack(mystack);
	SortStack(mystack);

	return 0;
}