#include <iostream>
#include <queue>

using namespace std;
#define MIN_SIZE 30
#define SIZE 130

struct HeapNode{
	HeapNode(){
		value = 0;
		freq = 0;
	}
	HeapNode(int v, int f){
		value = v;
		freq = f;
	}
	int value;
	int freq;
};

typedef struct HeapNode HNode;
typedef struct HeapNode* HNodePtr;
typedef struct HeapNode** HNodeDPtr;

void PrintValues(std::string name, const HNode& node){
	//cout << name.c_str() << " Val:[" << node.value << "],Frq:[" << node.freq << "]" << endl;
	return;
}
bool operator <(const HNode& lhs, const HNode& rhs){

	PrintValues("Left < ", lhs);
	PrintValues("Right < ", rhs);

	if(lhs.freq < rhs.freq){
		return true;
	}
	return false;
}

bool operator >(const HNode& lhs, const HNode& rhs){

	PrintValues("Left > ", lhs);
	PrintValues("Right > ", rhs);

	if(lhs.freq < rhs.freq){
		return false;
	}
	return true;
}

struct CompareHNode : public std::binary_function<HNodePtr, HNodePtr, bool>
{
	bool operator()(const HNodePtr lhs, const HNodePtr rhs) const
	{
		if(lhs->freq != rhs->freq){ 
			return lhs->freq < rhs->freq; 
		} else {
			return lhs->value > rhs->value;
		}
	}
};

int main(){

	int data[] = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};

	int value[SIZE] = {0};
	int values = 0;// sizeof(data) / sizeof(data[0]);

	//for Priority queue with Pointers
	priority_queue <HNodePtr, vector<HNodePtr>, CompareHNode > pQueue;

	//Following will not work
	//priority_queue <HNodePtr, vector<HNodePtr>, less<vector<HNodePtr>::value_type> > pQueue;

	//For PQ qith objects only
	//priority_queue <HNode, vector<HNode>, less<vector<HNode>::value_type> > pQueue;
	int T = 0;
	cin >> T;
	for(int test_case = 1; test_case <= T; test_case++){
		cin >> values;
		if(values < MIN_SIZE || values > SIZE) { cout << 0 << endl; continue; }
		for(int i = 0; i < values; i++){
			int v;
			cin >> v;
			value[v] += 1;
		}

		for(int i = 0; i < SIZE; i++){
			if(value[i] != 0){
				pQueue.push(new HNode(i, value[i]));
				//pQueue.push(HNode(i, value[i]));

			}
		}

		//Generate a new array and fill in all the the values according to its freq!
		int aI = 0;
		while(pQueue.size() > 0){
			HNodePtr ptr = nullptr;
			ptr = pQueue.top();
			//HNode ptr = pQueue.top();
			//cout << "Values:[" << ptr->value << "], Freq:[" << ptr->freq << "]" << endl;
			//cout << "Values:[" << ptr.value << "], Freq:[" << ptr.freq << "]" << endl;

			for(int i = 0; i < ptr->freq; i++){
				value[i+aI] = ptr->value;
			}
			aI += ptr->freq;
			pQueue.pop();
			delete ptr;
		}
		//cout << "Sort By Freq:[";
		for(int i = 0; i < values; i++){
			cout << value[i] << " ";
			//value[i] = 0;
		}
		cout << endl;
		//cout << "]" << endl;

		for(int i = 0; i < SIZE; i++){ value[i] = 0; }
		values = 0;
	}
	return 0;
}
