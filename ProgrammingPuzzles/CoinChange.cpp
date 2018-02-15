#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int minCoins = INT_MAX;

int cc(vector<int> arr, int val, vector<int> den){

	int res = 0;
	static int ways = 0;
	if (arr.size() <= 0){ return 0;}
	if ( val <0 ){ return 0;}
	if( val == 0 ){ 
		cout << "Way:[" << ++ways << "] : { ";   
		for ( int i = 0; i< den.size();i++){ cout << den[i] << " "; }
		cout << "}" << endl;

		if ( den.size() < INT_MAX){ minCoins = den.size(); }
		return 1;
	}

	//Add 0th element as the selected choice of Coin
	den.push_back(arr[0]);
	res += cc(arr, val-arr[0],den);

	//Remove inserted coin, as that choice has already been made and move on to the next choice.
	if ( den.size() > 0 ) { den.pop_back(); }

	arr.erase(arr.begin());
	res += cc(arr, val,den);
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

	vector<int> denominations;
	int NoOfWays = cc(coinArray,M, denominations);
	cout << "No Of Ways:["<< NoOfWays << "]" << endl;	
	cout << "Min Coins:[" << minCoins << "]" << endl;
}