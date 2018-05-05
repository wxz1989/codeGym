#include <iostream>

#define MAX_SIZE 105

using namespace std;

int MaxTip(int A[], int B[], int ac, int bc, int N, int X, int Y, int index){
	
	if ( index >= N ){ return 0;}

	if ( N <=0 ){ return 0;}
	if ( X < 0 || X > N ){ return 0;}
	if ( Y < 0 || Y > N ){ return 0;}

	if ( ac > X || bc > Y){ return 0;}


	int left =0;
	int right = 0;

	left = MaxTip(A, B, ac+1, bc, N, X,Y, index+1);
	//cout << "Left Is:" << left << endl;
	left += A[index];
	//cout << "Left Is Now:" << left << endl;

	right = MaxTip(A,B,ac,bc+1, N,X,Y, index+1);
	//cout << "Right Is:" << right  << endl;
	right += B[index];

	//cout << "Right Is Now:" << right  << endl;
	return (left > right ? left : right );
}

int main(){
	
	int A[MAX_SIZE] = {0};
	int B[MAX_SIZE] = {0};
	int N = 0;
	int X = 0, Y = 0;

	int test_cases;
	cin >> test_cases;

	for ( int tcs = 1; tcs <= test_cases ;tcs++){

		cin >> N;
		cin >> X;
		cin >> Y;

		for ( int i = 0 ;i < N;i++){ cin >> A[i]; }

		for ( int i = 0 ;i < N;i++){ cin >> B[i]; }

		cout << MaxTip(A, B, 0, 0, N, X, Y, 0) << endl ;

		for ( int i = 0 ;i < N;i++){ A[i] = B[i] = 0 ; }
		N = 0;
		X = 0;
		Y = 0;

	}

}