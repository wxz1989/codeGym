#include <iostream>

using namespace std;

#define MAX_ARRAY_SIZE 100

int N;
int permuteArr[MAX_ARRAY_SIZE] = { 0 };
int visited[MAX_ARRAY_SIZE] = { 0 };
int permString[MAX_ARRAY_SIZE] = {0};


void Reset();
bool IsValid(int index);
int Permute();
int PermuteRec(int array[], int length, int index, int count);

void Reset(){
	for (int i = 0; i < N; i++){
		permuteArr[i] = 0;
		visited[i] = 0;
	}
	N = 0;
}
bool IsValid(int index){
	if ((index < 0 || index > N) || visited[index]){
		return false;
	}
	return true;
}

int Permute(int arr[], int length){

	for (int i = 0; i < N; i++){  PermuteRec(permuteArr, length, i,0); 	}
	return 0;
}

int PermuteRec(int array[], int length, int index,int count){

	if (!IsValid(index)) { return 0; }
	if (length <= 0 || index < 0 ){ return 0; }

	visited[index] = 1;
	permString[count] = array[index];

	if (count == (length - 1)){  for (int i = 0; i < length; i++){ cout << permString[i] << " "; } cout<<endl; }

	int leftDir=0, rightDir = 0;
	for (leftDir = index - 1; leftDir >= 0; leftDir--){
		PermuteRec(array, length, leftDir, count +1);
	}

	for (rightDir= index + 1; rightDir <N; rightDir++){
		PermuteRec(array, length, rightDir, count + 1);
	}

	visited[index] = 0;
	return 1;
}

int main(int argc, char* argv[]){

	int test_cases = 0;
	freopen("Permutation_Sample_Input.txt", "r", stdin);

	cin >> test_cases;

	for (int tc = 0; tc < test_cases; tc++){
		cin >> N;
		for (int i = 0; i < N; i++){
			cin >> permuteArr[i];
			visited[i] = 0;
		}
		cout <<"================" << endl;
		cout <<"#:"<< tc+1 << endl;
		cout <<"================" << endl;
		Permute(permuteArr, N);
		Reset();
	}
	return 0;
}