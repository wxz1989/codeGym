
#include <iostream>

using namespace std;

#define MAX_N 7
#define MIN_N 3
#define MAX_M 5
#define MIN_M 2
#define ACCIDENT 9

//Constraints
int N = 0;
int M = 0;
int ANS = 0;

int mapMatrix[MAX_N][MAX_N];
int visitedMatrix[MAX_N][MAX_N];

int source = 0;
int dest = 0;

int minDistance = 999999999;
int pathCount = 0;

int Solve();
void Reset();
bool IsValid(int x, int y);
int ExhaustiveSeach(int x, int y, int distance);

int neighbours[4][2] = {
	{ 0, -1 },	//Left
	{ -1, 0 },	//Top
	{ 0, +1 },	//Right
	{ +1, 0 }	//Bottom
};

void Reset(){
	N = 0;
	M = 0;
	ANS = 0;

	for (int i = 0; i < MAX_N; i++){
		for (int j = 0; j < MAX_N; j++){
			mapMatrix[i][j] = 0;
			visitedMatrix[i][j] = 0;
		}
	}
	source = 0;
	dest = 0;
}

bool IsValid(int x, int y){
	if ((x >= 0 && x < N) &&
		(y >= 0 && y < N) &&
		mapMatrix[x][y] != 9){
		if (visitedMatrix[x][y] == 1) { return false; }
		return true;
	}
	return false;
}


int Solve(){

	int sp = 0;

	int finalResult = 1;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){

			if (dest > M) { return finalResult; }

			if (mapMatrix[i][j] == source){	//Start from here
				sp = ExhaustiveSeach(i, j, 0);

				if (pathCount != 0){ 
					finalResult *= pathCount; 
				} 
				else  { 
					if (dest == N && sp == 0){ 
						finalResult = 0; 
					} 
				}

				source++;
				dest = source + 1;

				pathCount = 0;
				minDistance = 999999999;
				i = 0;
				j = 0;
			}
		}
	}

	return finalResult;
}

int ExhaustiveSeach(int x, int y, int distance){

	int sp = 0;

	if (IsValid(x, y) == false){  return 0; }

	visitedMatrix[x][y] = 1;
	if (mapMatrix[x][y] == dest){	//If Desination Found then check and set minimum distance

		if (distance < minDistance){
			minDistance = distance;
			pathCount = 1;
		}
		else if (distance == minDistance){
			pathCount++;
		}
		return pathCount;
	}

	//Traverse in search of your dest
	if (distance >= minDistance){	 return sp;   }			//Pruning condition

	//Left,
	int nX = 0, nY = 0;
	nX = x + neighbours[0][0];
	nY = y + neighbours[0][1];
	if (IsValid(nX, nY)){
		sp = ExhaustiveSeach(nX, nY, distance + 1);
		visitedMatrix[nX][nY] = 0;
	}

	//Top
	nX = x + neighbours[1][0];
	nY = y + neighbours[1][1];
	if (IsValid(nX, nY)){
		sp = ExhaustiveSeach(nX, nY, distance + 1);
		visitedMatrix[nX][nY] = 0;
	}

	//Right
	nX = x + neighbours[2][0];
	nY = y + neighbours[2][1];
	if (IsValid(nX, nY)){
		sp = ExhaustiveSeach(nX, nY, distance + 1);
		visitedMatrix[nX][nY] = 0;
	}

	//Bottom
	nX = x + neighbours[3][0];
	nY = y + neighbours[1][1];
	if (IsValid(nX, nY)){
		sp = ExhaustiveSeach(nX, nY, distance + 1);
		visitedMatrix[nX][nY] = 0;
	}
	visitedMatrix[x][y] = 0;
	return sp;
}



int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("sample_input.txt", "r", stdin);
	//std::ios::sync_with_stdio(false);

	/*
	Read each test case from standard input.
	*/
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		Reset();
		cin >> N;
		cin >> M;
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				cin >> mapMatrix[i][j];
			}
		}

		source = 1;
		dest = source + 1;
		ANS = Solve();
		/////////////////////////////////////////////////////////////////////////////////////////////
		// Print the answer to standard output(screen).
		cout << "Case # " <<test_case <<" "<< ANS << endl;
	}
	//_getch();
	return 0; // Your program should return 0 on normal termination.
}
