#include <iostream>

#define MAX_LEN 100

using namespace std;

int MaxContSubSequence(int array[], int length);
void Reset();

int len = 0;
int arr[MAX_LEN] = {0};
int Ans = 0;

void Reset(){

	for ( int i = 0 ;i < MAX_LEN ;i++){
		arr[i] = 0;
	}
	len = 0;
	Ans = 0;
}

int MaxContSubSequence(int array[], int length){
	
	int maxSubSeq = 0;
	int sum = 0;
	int x = 0, y = 0;

	for ( int i = 0; i< length; i++){
		for (int j=i;j<length;j++){
			sum = 0;
			for (int k=i;k<=j;k++){
				sum += array[k];
			}
			if ( sum  > maxSubSeq ){
				maxSubSeq = sum;
			}
		}
	}
	return maxSubSeq;
}

int main(){

	
	int TC;
	cin >> TC;

	for ( int test_case = 0; test_case < TC;test_case++){

		cin >> len;
		for ( int i = 0 ;i < len ;i++){
			cin >> arr[i];
		}
		Ans = MaxContSubSequence(arr, len);
		cout <<"#"<< test_case+1<<" "<< Ans << endl;
		Reset();
	}

	return 0;
}