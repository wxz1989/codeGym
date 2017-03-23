#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_WIDTH 50
#define MAX_HEIGHT 50
#define MAX_BLOCKS ((MAX_WIDTH)*(MAX_HEIGHT))

int W=0, H = 0;
int foundBlocks = 0;
int distinctBlockCount =0;

int whiteBoard[MAX_HEIGHT][MAX_WIDTH] = {0};
int visitedArray[MAX_HEIGHT][MAX_WIDTH] = {0};

int blockCountArray[MAX_BLOCKS] = {0};

void PrintMatrix(int arr[MAX_HEIGHT][MAX_WIDTH]){
	cout <<"****************************" << endl;
	for ( int i = 0; i <H; i++){
		for ( int j = 0; j <W; j++){
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout <<"****************************" << endl;
}

bool IsValid(int i, int j){
	if ( (i >=0 && i<H) && 
		(j>=0 && j<W) &&
		visitedArray[i][j] == 0 && 
		whiteBoard[i][j] != 1)
	{
		return true;
	}
	return false;
}

void ResetData(){
	for ( int i = 0; i <H; i++){
		for ( int j = 0; j <W; j++){
			whiteBoard[i][j] = 0;
			visitedArray[i][j] = 0;
		}
	}
	
	for (int i = 0; i <distinctBlockCount; i++){ blockCountArray[i] = 0; }
	distinctBlockCount=0,W=0,H=0, foundBlocks=0;
}

int SortArray(int blockCount[], int length){
	if ( length <=0 ){ return -1;}
	for ( int i = 0;i < length; i++){
		for ( int j = i+1; j < length; j++){
			if ( blockCount[i] < blockCount[j]){
				int temp = blockCount[i];
				blockCount[i] = blockCount[j];
				blockCount[j] = temp;
			}
		}
	}
	return 1;
}

void DFSUtil( int arr[MAX_HEIGHT][MAX_WIDTH], int i, int j){
	if(!IsValid(i, j)){ return; }

	foundBlocks++;
	visitedArray[i][j] = 1;
//PrintVisitedMatrix();
//Go right
	DFSUtil(arr, i, j+1);

//Go Bottom
	DFSUtil(arr, i+1, j); 
//Go Left
	DFSUtil(arr, i, j-1);

//Go Top
	DFSUtil(arr, i-1,j);
}

int DFS( int arr[MAX_HEIGHT][MAX_WIDTH], int i, int j){

	int redBlocks = 0;
	for ( int i =0; i< H;i++){
		for ( int j =0; j< W; j++){
			if ( visitedArray[i][j] == 0 && arr[i][j] != 1){

				//Recursive function calls to get Total Block Counts for every available section
				
				DFSUtil(arr, i, j);
				blockCountArray[distinctBlockCount++] = foundBlocks;

				cout << "UnPainted blocks:[" <<i <<"," << j <<  "]:" << foundBlocks << endl;
				//Reset the Global varialbe for total blocks found
				foundBlocks = 0;
			}
		}
	}
	SortArray(blockCountArray, distinctBlockCount);
	

	for ( int i = 0;i < distinctBlockCount; i++){ if ( i % 3 == 0 ){ redBlocks += blockCountArray[i]; } }
	return redBlocks;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("ColorMapping.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; test_case++){
		cin >> W; 
		cin >> H;

		for ( int i = 0; i< H; i++){
			for ( int j = 0; j< W;j++){
				int value;
				cin >> value;
				whiteBoard[i][j] = value;
				visitedArray[i][j] = value;
			}
		}
		int Ans = 0;
		Ans = DFS(whiteBoard, 0,0);
		// Print the answer to standard output(screen).
		//PrintMatrix(whiteBoard);
		//PrintMatrix(visitedArray);
		cout << "#" << test_case << " " << Ans << endl;
		ResetData();
	}

return 0; // Your program should return 0 on normal termination.
}
