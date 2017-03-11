#include <iostream>
using namespace std;

#define MAX_VAL 100
int N, M;

int ArrayValues[MAX_VAL] ={0};

void Reset(){

	for ( int i = 0; i< M;i++)
	{
		 ArrayValues[i] = 0;
	}
}

int Solve(){

	for ( int i = 0; i< M;i++)
	{
		int Sel = ArrayValues[i];
		int diff = N - Sel;
		if( diff  < 0 ) { continue; }
		for ( int j = i+1; j< M;j++)
		{
			 if ( ArrayValues[j] == diff){
			 	return 1;
			 }
		}
	}
	return 0;
}

int main() {

		cin >> N;
		cin >> M;

		if (  N <=0 || M <= 0 ){ cout << 0 << endl; return;}
		
		for ( int i = 0; i< M;i++)
		{
			cin >> ArrayValues[i];
		}

		int Ans = Solve();
		cout << Ans << endl;
		Reset();
		return 0;
}