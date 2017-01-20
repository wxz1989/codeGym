#include <iostream>

using namespace std;

#define MAX_ARRAY_SIZE 100

int combCount= 0, totalCombi = 0;
int N, R;
int permuteArr[MAX_ARRAY_SIZE] = { 0 };
int permString[MAX_ARRAY_SIZE] = {0};


void 	Reset();
int     CombinateRec(int array[], int length, int index, int visitedIndex, int count, int Result[]);

void Reset(){
	for (int i = 0; i < N; i++){
		permuteArr[i] = 0;
		permString[i] = 0;
	}
	N =R= 0;
	combCount = totalCombi = 0;
}

void Combinate(int array[], int length, int index, int visitedIndex, int count, int Result[]){
	for ( int i = 0; i < length; i++){
		CombinateRec(array, length, i, 0, count, Result);
	}
}

int 
CombinateRec(int array[], int length, int index, int visitedIndex, int count, int Result[]){

	if ( length <=0 || index <0 || visitedIndex < 0|| count < 0 ){
		return 0;
	}

	Result[visitedIndex] = array[index];

	if ( visitedIndex == (count-1)){
		combCount++;
		cout << combCount <<": ";
		for( int j = 0; j< count;j++){
			cout <<  Result[j] << " ";
		}
		cout << endl;
		return 1; 
	}

	for (int k = index+1; k < length; k++){
		CombinateRec(array, length, k, visitedIndex+1, count, Result);
	}
	return 0;
}


int main(int argc, char* argv[]){

	int test_cases = 0;
	freopen("CombiSampleInput.txt", "r", stdin);

	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){
		cin >> N;
		cin >> R;
		for (int i = 0; i < N; i++){
			cin >> permuteArr[i];
		}
		cout <<"================" << endl;
		cout <<"#:"<< tc+1 << endl;
		cout <<"================" << endl;
		//CombinateRec(permuteArr, N, 0, 0, R, permString);
		Combinate(permuteArr, N, 0, 0, R, permString);
		Reset();
	}
	return 0;
}