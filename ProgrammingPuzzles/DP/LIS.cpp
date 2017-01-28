#include <iostream>
#include <stdio.h>
#include <ctime>
#include <time.h>
 
#define MAX_ARRAY_LENGTH 1000000

using namespace std;

int Ans = 0;
int LISArrayLength = 0;
int LISArray[MAX_ARRAY_LENGTH] = { 0 };
int Sum[MAX_ARRAY_LENGTH] = { 0 };
int Length[MAX_ARRAY_LENGTH] = { 0 };
int SeqArray[MAX_ARRAY_LENGTH] = {0};

void Reset();
void PrintLength();
void PrintSum();
int LIS(int a[], int& length);

void Reset(){
	for (int i = 0; i < LISArrayLength ; i++){  LISArray[i] = 0; }
	LISArrayLength = 0;
	Ans = 0;
}

void PrintLength(){
	std::cout<<"Length:";
	for (int i = 0; i < LISArrayLength; i++){
		cout << Length[i] << "," ;
	}
	cout << endl;
}
void PrintSum(){
	cout<<"Sum:";
	for (int i = 0; i < LISArrayLength; i++){
		cout << Sum[i] << ",";
	}
	cout << endl;
}

int LISDP(int a[], int length){
	clock_t start, end;
	double cpu_time_used;
     
    start = clock();
    
     
	int maxSum = 0;
	if (length <=0 ){ return 0;}
	int LIS[100]= {1};

	for ( int j = 0; j < length; j++){
		LIS[j] = 1;
	}

	for ( int i = 1; i< length ; i++){
		for ( int j = 0; j < i; j++){
			if ( a[j] < a[i] ){
				LIS[i]	= ((LIS[i] < LIS[j]+1) ? LIS[j]+1 : LIS[i]);
			}
		}
	}

	std::cout <<"LIS: ";
	for ( int j = 0; j < length; j++){
		std::cout << LIS[j] << " ";
	}
	std::cout <<std::endl;

	for ( int j = 0; j < length; j++){
		if ( maxSum < LIS[j]){
			maxSum = LIS[j];
		}
	}
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("LISDP : %lf",cpu_time_used);
	cout <<endl;
	return maxSum;
}

int LISRecursive(int a[], int c, int j, int N, int sum){

	int finalSum =0;
	if ( c > N || j> N ){
		return finalSum;
	}
	int ret = 0;
	return finalSum;
}


int LIS(int a[], int& length){
	clock_t start, end;
	double cpu_time_used;
     
    start = clock();

	unsigned int maxLength = 0;
	unsigned int maxSum = 0;

	int iIndex = 0;
	int c = 0;
	for (int i = 0; i < LISArrayLength; i++){
		unsigned int localLength = 1;
		unsigned int localSum = LISArray[i];
		c = i;

		//Seq[iIndex++] = a[c];
		for (int j = i+1; j < LISArrayLength; j++){
			if (a[c] < a[j]){
				c = j;
				localSum += a[c];
				//Seq[iIndex++] = a[c];
				localLength++;
			}
		}
		if (localSum > maxSum){
			maxSum = localSum;
		}
		if (localLength > maxLength){
			maxLength = localLength; 
		}
		Sum[i] = localSum;
		Length[i] = localLength;
	}
	PrintSum();
	PrintLength();
	length = maxLength;

	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("LIS: %lf",cpu_time_used);
	cout << endl;
	return maxSum;
}

int main(){
	int TC = 0;
	freopen("LIS_input.txt", "r", stdin);

	cin >> TC;
	
	for (int test_cases = 0; test_cases < TC; test_cases++){
		cin >> LISArrayLength;
		for (int i = 0; i < LISArrayLength; i++){
			int val = 0;
			cin >> val;
			LISArray[i] = val;
		}
		int mL;
		Ans = LIS(LISArray, mL);
		int Ans1 = LISDP(LISArray, LISArrayLength);

		std::cout <<"# " << test_cases+1 <<" [Sum: "<< Ans << " Length: " <<  mL <<"]" <<std::endl;
		std::cout <<"# " << test_cases+1 <<" " <<  Ans1 << std::endl;
		Reset();
	}
	return 0;
}