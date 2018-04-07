#include <iostream>
#include <limits>
#include <vector>

#define MAX_SIZE 999

using namespace std;

int minCoins = INT_MAX;
int table[MAX_SIZE]= {-1};
int Sum = 0;

void ResetTable(int arr[], int size){
	for ( int i = 0; i<=size;i++){
		arr[i] = -1;
	}
	table[0] = 0;
}
void PrintTable(int arr[], int size){
	cout << "Table:[";
	for ( int i = 0; i<=Sum;i++){
		cout << arr[i] << " ";
	}
	cout << "]" << endl;
}

int cc(vector<int> arr, int val, vector<int> den){

	static int ways = 0;

	int res = 0;
	if (arr.size() <= 0){ return 0;}
	if ( val <0 ){ return 0;}
	if( val == 0 ){ 
		cout << "Way:[" << ++ways << "] : { ";   
		for ( int i = 0; i< den.size();i++){ cout << den[i] << " "; }
		cout << "}" << endl;

		if ( den.size() < minCoins ){ minCoins = den.size(); }
		return 1;
	}

	//Add 0th element as the selected choice of Coin
	//if ( table[val] == -1 ){

		den.push_back(arr[0]);
		res += cc(arr, val-arr[0],den);
		table[val-arr[0]] = res;
		PrintTable(table,arr.size());

		//Remove inserted coin, as that choice has already been made and move on to the next choice.
		if ( den.size() > 0 ) { den.pop_back(); }

		arr.erase(arr.begin());
		res += cc(arr, val,den);
		//table[val] = res;
		PrintTable(table,arr.size());

	/*} else {
		res = table[val];
	}*/
	return res;
}

int main(){

	int M= 0, N = 0;
	cin >> M;
	cin >> N;

	vector<int> coinArray;	

	for ( int i = 0; i<N;i++){
		int val= 0;
		cin >> val;
		coinArray.push_back(val);
	}

	Sum = M;
	ResetTable(table, M);
	PrintTable(table,M);
	vector<int> denominations;
	int NoOfWays = cc(coinArray,M, denominations);
	cout << "No Of Ways:["<< NoOfWays << "]" << endl;	
	cout << "Min Coins:[" << minCoins << "]" << endl;
}