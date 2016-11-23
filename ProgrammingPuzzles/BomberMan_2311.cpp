#include <iostream>

#define MIN_BOMBS 1
#define MAX_BOMBS 4
#define MIN_WIDTH 2
#define MAX_WIDTH 12
#define MIN_HEIGHT 2
#define MAX_HEIGHT 15
#define BOMBED -1
#define VACATED -2
#define EMPTY 0
#define MAX_NEIGHBOURS 4
#define NEIGHBOURS_INDEX 2
#define MAX_VALUE  9999999


/* CORRECT OUTPUT OF THE FIRST 5 SAMPLE INPUT
#1 12
#2 27
#3 4
#4 8
#50 
*/

int N = 0;
int W = 0;
int H = 0;
int Ans = 0;
int minBlocks = MAX_VALUE;
int bombingArray[MAX_WIDTH][MAX_HEIGHT] = { 0 };
int workingArray[MAX_WIDTH][MAX_HEIGHT] = { 0 };

int neighbours[MAX_NEIGHBOURS][NEIGHBOURS_INDEX] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } };

using namespace std;

void Print(std::string message){
	std::cout << "********" << message.c_str() << "********" << std::endl;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			std::cout << workingArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "************************" << std::endl;
}

bool IsValid(int i, int j){
	if ((i >= 0 && i < H) && (j >= 0 && j < W)){
		return true; //there is a valid number here and can be bombed as well
	}
	return false;
}

int CountBlocks(){
	int bC = 0;
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if (workingArray[i][j] >= 1 && workingArray[i][j] <= 9){
				bC++;
			}
		}
	}
	return bC;
}

void Reset(){

	for (int i = 0; i < MAX_HEIGHT; i++){
		for (int j = 0; j < MAX_WIDTH; j++){
			bombingArray[i][j] = 0;
			workingArray[i][j] = 0;
		}
	}
	Ans = N = W = H = 0;
	minBlocks = MAX_VALUE;
}

void ReInit(){
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			workingArray[i][j] = bombingArray[i][j];
		}
	}
}

void ReArrangeBlocks(){
	for (int i = H - 1; i >= 0; i--){
		for (int j = W - 1; j >= 0; j--){
			//if (workingArray[i][j] == BOMBED || workingArray[i][j] == VACATED){
			if (workingArray[i][j] == EMPTY){
				//If this node is vacated or have been bombed then find a valid node in that column
				int k = 0;
				if (i > 0){
					for (k = i-1; k > 0; k--){
						if (workingArray[k][j] >= 1 && workingArray[k][j] <= 9){  break; }
						else{ continue; }
					}

					if (k >= 0 && k != i){
						workingArray[i][j] = workingArray[k][j];
					}
				}
				else {
					workingArray[i][j] = 0;
				}
				for (int l = k; l < i; l++){
					workingArray[l][j] = VACATED;
				}
			}
		}
	}

	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			if (workingArray[i][j] == VACATED){
				workingArray[i][j] = EMPTY;
			}
		}
	}
}



int Bomb(int i, int j, int rangeRemaining){

	if (IsValid(i, j) == false){ return -5; }
	if (rangeRemaining < 0) { return 0; }
	int blockValue = workingArray[i][j];
	int range = blockValue - 1;
	if (blockValue >= 1 && blockValue <= 9){
		workingArray[i][j] = EMPTY;
	}

	if (blockValue > 0 && range > 0){
		//Visit Left
		int ret = -3;
		
		/*
		for (int z = 0; z < MAX_NEIGHBOURS; z++){
			int nX = 0, nY = 0;
			nX = i + neighbours[z][0];
			nY = i + neighbours[z][1];
		}
		*/

		for (int r = 1; r <= range; r++){
			ret = Bomb(i, j-r, range - r);
		}
		
		//Visit Top
		for (int r = 1; r <= range; r++){
			ret = Bomb(i - r, j, range - r);
		}
		//Visit Right
		for (int r = 1; r <= range; r++){
			ret = Bomb(i, j + r, range - r);
		}
		//Visit Bottom
		for (int r = 1; r <= range; r++){
			ret = Bomb(i + r, j, range - r);
		}
	}// range is negative and hence continue...
	return 1;
}

int Solve(int x, int y){

	int blocks = 0;
	bool bombDroped;
	for (int bC = 0; bC < N; bC++){
		bombDroped = false;
		for (int i = x; i < H; i++){
			for (int j = y; j < W; j++){
				if ((workingArray[i][j] >= 1 && workingArray[i][j] <= 9)){
					//cout <<"Bomb# "<<bC+1<<endl;
					int BC = Bomb(i, j, minBlocks);
					//Print("Before");
					ReArrangeBlocks();
					//Print("After");
					bombDroped = true;
					break;
				}
				if (bombDroped){ break; }
			}
			if (bombDroped){ break; }
		}
	}

	blocks = CountBlocks();
	if (blocks < minBlocks){
		//cout << "Blocks(After 3 bombs):" << blocks << endl;
		minBlocks = blocks;
	}
	return minBlocks;
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("Bomberman_Sample_Input.txt", "r", stdin);

	cin >> T;
	for (test_case = 1; test_case <= T; test_case++)
	{
		cin >> N;
		cin >> W;
		cin >> H;	

		for (int i = 0; i < H; i++){
			for (int j = 0; j < W; j++){
				int val = 0;
				cin >> val;
				bombingArray[i][j] = workingArray[i][j] = val;
			}
		}

		for (int i = 0; i < H; i++){
			for (int j = 0; j < W; j++){
				Ans = Solve(i, j);
				ReInit();
			}
		}
		// Print the answer to standard output(screen
		cout << "#" << test_case << " " << Ans << endl;
		Reset();
	}
	return 0; // Your program should return 0 on normal termination.
}