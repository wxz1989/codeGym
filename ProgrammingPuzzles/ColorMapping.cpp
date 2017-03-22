#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_WIDTH 50
#define MAX_HEIGHT 50
#define MAX_BLOCKS ((MAX_WIDTH)*(MAX_HEIGHT))

int W=0, H = 0;
int TotalRAreas = 0;
int whiteBoard[MAX_HEIGHT][MAX_WIDTH] = {0};
int visitedArray[MAX_HEIGHT][MAX_WIDTH] = {0};
int blockCountIndex =0;
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
		visitedArray[i][j] == 0 && whiteBoard[i][j] != 1){
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
	
	for (int i = 0; i <MAX_BLOCKS; i++){ blockCountArray[i] = 0; }
	blockCountIndex = 0,W=0, H = 0,TotalRAreas = 0;
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

int DFSUtil( int arr[MAX_HEIGHT][MAX_WIDTH], int i, int j, int count, int dir){
	int ret = 0;
	if(!IsValid(i, j)){ return 0; }
	TotalRAreas++;

	visitedArray[i][j] = 1;
//PrintVisitedMatrix();
//Go right
	ret = DFSUtil(arr, i, j+1, count+1, 0);

//Go Bottom
	ret = DFSUtil(arr, i+1, j, count+1, 1); 
//Go Left
	ret = DFSUtil(arr, i, j-1, count+1, 1);

//Go Top
	ret = DFSUtil(arr, i-1,j, count+1, 1);
	return count;
}

int DFS( int arr[MAX_HEIGHT][MAX_WIDTH], int i, int j){
	int currnetCount =0;
	int count = 0;
	for ( int i =0; i< H;i++){
		for ( int j =0; j< W; j++){
			if ( visitedArray[i][j] == 0 && arr[i][j] != 1){
				int retValue = DFSUtil(arr, i, j, 0, count);
				blockCountArray[blockCountIndex++] = TotalRAreas;
				TotalRAreas = 0;
			}
		}
	}
	SortArray(blockCountArray, blockCountIndex);
	int rValues = 0;
	for ( int i = 0;i < blockCountIndex; i++){
		if ( i % 3 == 0 ){
			rValues += blockCountArray[i];
		}
	}
	return rValues;
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
		PrintMatrix(visitedArray);
		cout << "#" << test_case << " " << Ans << endl;
		ResetData();
	}

return 0; // Your program should return 0 on normal termination.
}
