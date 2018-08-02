#include <iostream>
#include <conio.h>

using namespace std;
#define SIZE 100

int Seq[SIZE] = {0};
int MSIS[SIZE] = {0};
int Ans = -999999;

int start = 0; 
int End = 0;

int Solve(int arr[], int size){
	for (int i = 1; i < size; i++){
		for (int j = 0; j < i; j++){
			if (arr[j] < arr[i]){

				start = j;
				if (MSIS[i] == 0){ MSIS[i] = arr[i] + arr[j]; }
				else { MSIS[i] += arr[j]; }

				if (MSIS[i] > Ans ){  
					Ans= MSIS[i]; 
					End = i;
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


void SwapArray(int arr[], int size, int swapSize){
	if (size <= 0 || swapSize <=0 ){ return; }
	int start = 0;
	int end = 0;
	int mid = 0;
	if (swapSize == 2){
		for (start = 1; start <size; start += swapSize){
			int temp = arr[start-1];
			arr[start-1] = arr[start];
			arr[start] = temp;
		}
		return;
	}
	else {
		for (start = 0; start < size; ){
			{
				if ((start + swapSize) < size){
					end = (start + swapSize) - 1;
					mid = (start + end) / 2;
				}
				else if (start < size){
					end = size - 1;
					mid = (start + end) / 2;
				}
				else {
					start = size;
					return;
				}
				int temp = 0;
				if (swapSize % 2 == 0){
					for (;(start < end);){
						temp = arr[start];
						arr[start] = arr[end];
						arr[end] = temp;
						start++;
						end--;
					}
					start = (start + swapSize/2);
				}
				else {
					for (; start < mid, end > mid; ){
						temp = arr[start];
						arr[start] = arr[end];
						arr[end] = temp;
						start++;
						end--;
					}
					start = (start + swapSize / 2)+1;
				}
			}
		}
	}
	//Swap the leftOvers if any.
}
void PrintArray(int arr[], int size){
	cout << "Arr:[";
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	cout << "]" << endl;
}
int main(){

	int data[] = { 1, 102, 2, 3, 100, 4, 5,99 };
	int arraySize = sizeof(data) / sizeof(int);

	//int data[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
	for (int i = 0; i < arraySize ; i++){
		Seq[i] = data[i];
		//MSIS[i] = Seq[i];
	}
	int swapSize = 0;
	cout << "MaxSum Incr. SubSeq. :[" << Solve(Seq, arraySize) << "]" << endl;
	PrintArray(Seq, arraySize);
	cout << "Enter SwapSize:";
	cin >> swapSize;
	SwapArray(Seq, arraySize, swapSize);
	PrintArray(Seq, arraySize);
	_getche();
	return 0;
}
