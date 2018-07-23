#include <iostream>
#include <queue>
#include <conio.h>
#include <functional>

using namespace std;

vector<double> runningMedian(vector<int> stream){
	vector<double> rm;
	int count = 0;
	double median = 0, divisor = 2.0;

	priority_queue<int> maxHeap;
	priority_queue<int, std::vector<int>, std::greater<int>> minHeap;


	for (unsigned int i = 0;  i< stream.size(); i++){
		int ele = stream[i];

		if (maxHeap.size() && ele > maxHeap.top()){
			minHeap.push(ele);
		} else {
			maxHeap.push(ele);
		}

		int temp = 0;
		if (abs(maxHeap.size() - minHeap.size() > 1)){
			if (maxHeap.size() > minHeap.size()){
				temp = maxHeap.top();
				maxHeap.pop();
				minHeap.push(temp);
			}
			else {
				temp = minHeap.top();
				minHeap.pop();
				maxHeap.push(temp);
			}
		}

		//Error-1 : When there is only 1 element in the stream.
		if (i == 0){ 
			if ( maxHeap.size() > 0){
				median = maxHeap.top();
			} else {
				median = minHeap.top();
			}
		}
		else {
			if ( (i+1) % 2 == 1){			//Error-2 : Stream size is dynamic, hence use i instead of stream size.
				if (maxHeap.size() > minHeap.size()){ median = maxHeap.top(); } 
				else { median = minHeap.top(); }
			}
			else {
				median += maxHeap.top();
				median += minHeap.top();
				median /= divisor;
			}
			rm.push_back(median);
		}
		cout << "Median:[" << median << "]" << endl;
		median = 0;
	}
	return rm;
}
int main(){

	//int data[] = { 12, 4, 5, 3, 8, 7 };
	//int data[] = { 1,2,3,4,5,6,7,8,9,10};
	int data[] = { 5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4 };

	vector<double> rm;
	vector<int> stream(data, data + 12);
	rm = runningMedian(stream);
	_getche();

	return 0;
}
