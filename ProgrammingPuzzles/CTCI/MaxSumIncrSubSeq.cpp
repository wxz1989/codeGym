#include <iostream>
#include <conio.h>

using namespace std;
#define SIZE 100

int Seq[SIZE] = {0};
int MSIS[SIZE] = {0};
int Ans = -999999;

int Solve(int arr[], int size){
	for (int i = 1; i < size; i++){
		for (int j = 0; j < i; j++){
			if (arr[j] < arr[i]){
				if (MSIS[i] == 0){
					MSIS[i] = arr[i] + arr[j];
				}
				else {
					MSIS[i] += arr[j];
				}
				if (MSIS[i] > Ans ){
					Ans= MSIS[i];
				}
			}
		}
	}
	return Ans;
}

void Reset(int size = SIZE){
	for (int i = 0; i < size; i++){
		Seq[i] = 0;
		MSIS[i] = 0;
	}
	Ans = 0;
}
int main(){

	//int data[] = { 1, 102, 2, 3, 100, 4, 5 };
	int data[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	for (int i = 0; i < sizeof(data) / sizeof(int); i++){
		Seq[i] = data[i];
		//MSIS[i] = Seq[i];
	}
	cout << "MaxSum Incr. SubSeq. :[" << Solve(Seq, sizeof(data) / sizeof(int)) << "]" << endl;;
	_getche();
	return 0;
}
