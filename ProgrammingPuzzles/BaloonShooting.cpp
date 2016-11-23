#include<iostream>

using namespace std;

#define MAX_BALOONS 45
#define MIN_BALOONS 1
#define MAX_K		1000000

int ballonArray[MAX_BALOONS];
int WorkingArray[MAX_BALOONS];
int workingArraySize = 0;

int N;
int K;
int Ans = 0;
int minimumBallons = 999999999;

void	Reset();
int		Solve();
int		FinMinBallons(int N);
void	RemoveFromArray(int centerIndex, int remBallons);

void Reset(){
	for (int i = 0; i < MAX_BALOONS; i++){ ballonArray[i] = 0; WorkingArray[i] = 0; }
	N = 0;
	K = 0;
	Ans = 0;
	minimumBallons = 0;
}

void RemoveFromArray(int centerIndex, int remBallons){

	if (remBallons == 0) return;
	if (centerIndex == 0 || centerIndex == N){ return; }

	for (int i = 0; i < MAX_BALOONS; i++){ WorkingArray[i] = 0; }

	for (int i = 0, j = 0; i < N; i++){
		if ((i == centerIndex - 1) || (i == centerIndex) || (i == centerIndex + 1)){ continue; }
		WorkingArray[j] = ballonArray[i];
		j++;
	}
}

int Solve(){

	if (N < 3){ return N; }

	int min = 0;
	workingArraySize = N;

	min = FinMinBallons(workingArraySize);
	if (min < minimumBallons){
		minimumBallons = min;
	}
	return min;
}

int FinMinBallons(int ballons){

	int minB = 0;

	//Termination conditions
	if (ballons < 3) { return ballons; }
	if (ballons == 0){ return minB; }

	//Try all options
	for (int i = 1; i < ballons - 1; i++){

		int a, b, c;
		c = WorkingArray[i + 1];
		b = WorkingArray[i];
		a = WorkingArray[i - 1];

		if (abs(c - b) == K && abs(b - a) == K){
			//condition matches, remove this members and call this same function with update array and recod min
			ballons -= 3;
			RemoveFromArray(b, ballons);
			minB = FinMinBallons(ballons);
			if (minB != 0)
				minB = ballons;
		}
		/*else {
			minB = ballons;
		}*/
	}
	return minB;
}
int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		cin >> K;

		for (int i = 0; i < N; i++){ cin >> ballonArray[i]; WorkingArray[i] = ballonArray[i]; }
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		Ans = Solve();

		cout << "#" << test_case << " " << Ans << endl;
		Reset();
	}
	return 0;//Your program should return 0 on normal termination.
}