#include <iostream>
#include <climits>

using namespace std;

int Max(int a, int b){ return (a > b) ? a : b; }


int MaxSum(int A[], int n){

	int maxSumSoFar = 0;
	int maxISoFar = 0;
	int maxJSoFar = -1;
	for (int i = 0; i < n; i++){
		int sum = 0;
		for (int j = i; j<n; j++){
			sum += A[j]; //sum is that of A[i..j]
			if (sum>maxSumSoFar){
				maxSumSoFar = sum;
				maxISoFar = i;
				maxJSoFar = j;
			}
		}
	}
	cout << "Start:[" << maxISoFar << "] End:[" << maxJSoFar << "]" << endl;
	return maxSumSoFar;
}


int MaxSumDC(int arr[], int low, int high){

	if (low == high){ return arr[low]; }

	int mid = (low + high) / 2;

	int sum = 0;
	int rightMax = INT_MIN ,leftMax = INT_MIN;
	for (int i = mid; i >=low; i--){
		sum += arr[i];
		if (sum > leftMax ){
			leftMax = sum;
		}
	}
	
	sum = 0;
	for (int i = mid+1; i <=high; i++){
		sum += arr[i];
		if ( sum  > rightMax ){
			rightMax = sum;
		}
	}

	int maxLeftRight = Max(MaxSumDC(arr, low, mid), MaxSumDC(arr, mid + 1, high));	
	return Max(maxLeftRight, leftMax + rightMax);
}


int main(){

	int a[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	int n = sizeof(a) / sizeof(a[0]);
	//int max_sum = MaxSum(a, n);
	int max_sum = 0;
	max_sum = MaxSumDC(a, 0, n -1);
	cout << "Maximum contiguous sum is " << max_sum << endl;
	max_sum = MaxSum(a, n);
	cout << "Maximum contiguous sum is " << max_sum << endl;
	return 0;
}
