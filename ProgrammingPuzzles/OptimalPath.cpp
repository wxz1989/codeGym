#include<iostream>

#include <conio.h>

#define SIZE 100

using namespace std;

struct CoOrdinates{
	int x;
	int y;
	bool visited;
	CoOrdinates(){
		x = -1;
		y = -1;
		visited = false;
	}
	CoOrdinates(int i, int j){
		x = i;
		y = j;
	}
	void Reset(){
		x = -1;
		y = -1;
		visited = false;
	}

};

typedef struct CoOrdinates Loc;
int N = 0;
Loc ofc, home;
Loc matt[SIZE];
int dist[SIZE]= { 9999999 };

void Reset(int size = SIZE){

	for (int i = 0; i < size; i++){ 
		matt[i].Reset(); 
		dist[i] = 9999999;
	}
	ofc.Reset();
	home.Reset();
	
	N=0;
}

int getDistance(Loc s, Loc d){
	int dX = 0,dY = 0;
	if (s.x > d.x){
		dX = s.x - d.x;
	}
	else {
		dX = d.x - s.x;
	}

	if (s.y > d.y){
		dY = s.y - d.y;
	}
	else {
		dY = d.y - s.y;
	}
	return (dX+dY);
}

int DFSUtil(Loc next){

	int greedyNext = -1;
	int minDistance = 9999999;

	for (int i = 0; i < N; i++){
		if (greedyNext == i || matt[i].visited){ continue; }
		int d = getDistance(next, matt[i]);
		if (dist[i] > d){
			dist[i] = d;
		}
		if (d < minDistance){
			minDistance = d;
			greedyNext = i;
		}
	}
	return greedyNext;
}

int DFS(Loc start){
	Loc next;
	int greedyNext = -1;
	int cost = 0;
	int past = 0;

	greedyNext = DFSUtil(start);
	cost += dist[greedyNext];
	matt[greedyNext].visited = true;
	//cout << "Sequence :[ (" << start.x << "," << start.y << "), ";
	//cout << " (" << matt[greedyNext].x << "," << matt[greedyNext].y << "), ";

	while (greedyNext != -1){
		next = matt[greedyNext];
		greedyNext = DFSUtil(next);
		if (greedyNext != -1){
			matt[greedyNext].visited = true;
			cost += dist[greedyNext];
			//cout << " (" << matt[greedyNext].x << "," << matt[greedyNext].y << "), ";
			past = greedyNext;
		}
	}
	//cout << "]" << endl;
	cost += getDistance(matt[past], home);
	//cout << "Cost :[" << cost << "]" << endl;
	
	return cost;// greedyNext;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	The freopen function below opens input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("OptimalPathSampleInput.txt", "r", stdin);
	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		if (N == 0)
			Reset();
		else
			Reset(N);
		cin >> N;
		
		int x = 0, y = 0;
		cin >> x;
		cin >> y;

		ofc.x = x;
		ofc.y = y;

		cin >> x;
		cin >> y;

		home.x = x;
		home.y = y;

		for (int i = 0; i < N; i++){
			cin >> x;
			cin >> y;

			matt[i].x = x;
			matt[i].y = y;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		cout << "#" << test_case << " " << DFS(ofc) << endl;

	}
	_getche();
	return 0;//Your program should return 0 on normal termination.
}
