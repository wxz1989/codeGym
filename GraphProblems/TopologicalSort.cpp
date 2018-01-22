#include <bits/stdc++.h>
#include "Graph_Impl.h"


using namespace std;

#define MAX 100

void Test_SampleInput(){
	int test_cases = 0;
	int size= 0;

	freopen("TSort_Sample_Input.txt", "r", stdin);
	cin >> test_cases;

	Graph gObj;

	int v = 0;
	int e = 0;
	cout << "#TCs" << test_cases <<  endl;
	for (int tc = 0; tc < test_cases; tc++){
		cout << "# " << tc <<  endl;

		cin >> v;
		cin >> e;

		gObj.Init(v,e);

		int value = 0;
		int source=0, dest = 0;
		for (int i = 0; i < e; i++){ 
			cin >> source ;
			cin >> dest ;

			gObj.AddEdge(source,dest);

		}
		gObj.TopologicalSort();
		//gObj.Release();
	}
}
void Test_RandomisedDataInput(){

	/*srand(time(nullptr));
	v = rand() % 10;
	srand(time(nullptr));
	e = rand() % 10;
	srand(time(nullptr));

	int source = 0; int dest = 0;

	for (int i = 0; i< e; i++){

		source  = rand() % v;
		dest  = rand() % v;
		srand(time(nullptr));
	
		adjList[source][dest] = 1;
	}
	TopologicalSort();*/
}

int main(int argc, char* argv[]){

	cout << "Arg Count:" << argc << endl;
	if (argc > 1){
		cout << "Arg :" << argv[1] << endl;
		if (strcmp(argv[1], "0") == 0){
			Test_SampleInput();
		}
		else if (strcmp(argv[1], "1") == 0){
			Test_RandomisedDataInput();
		}
		else {
			Test_SampleInput();
		}
	} else {
		Test_SampleInput();
	}
	return 0;
}
