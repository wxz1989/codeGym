#include <iostream>
#include <queue>
#include <conio.h>
#include <functional>
#include <iomanip>
//#include <concurrent_priority_queue.h>

using namespace std;

#define SIZE 10

int main(){

	//int data[] = { 12, 4, 5, 3, 8, 7 };
	int data[] = { 1,2,3,4,5,6,7,8,9,10};
	int count = 0;
	double median = 0;

	std::setprecision(1);

	priority_queue<int> maxHeap;
	priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	
	priority_queue<int> maxTemp;
	priority_queue<int, std::vector<int>, std::greater<int>> minTemp;
	
	for (count = 1; count <=SIZE; count++){
		maxHeap.push(data[count-1]);
		minHeap.push(data[count-1]);
		
		double minT = 0;
		double maxT = 0;

		if (count > 2){
			if (count % 2 == 0){

				maxTemp = maxHeap;
				minTemp = minHeap;

				maxTemp.pop();
				minTemp.pop();

				minT = minTemp.top();
				maxT = maxTemp.top();

				if (maxT == minT){
					median = maxT;
				} else {
					median = double(minT + maxT) / 2.0;
				}
			}
			else{
				int popOperation = 0;
				if (count > 3){
					popOperation = (count-1) - 2;					
				}
				else {
					popOperation = (count) - 2;
				}

				maxTemp = maxHeap;
				minTemp = minHeap; 

				for (int j = 0; j < popOperation; j++){
					maxTemp.pop();
					minTemp.pop();
				}

				minT = minTemp.top();
				maxT = maxTemp.top();
				
				if (minT == maxT){
					median = maxT;
				}
				else {
					median = double(minT + maxT) / 2.0;
				}
			}
		} else{
			if (count == 1){
				median = data[0];
			} else { 
				median = double((data[0] + data[1]) / 2.0);
			}
		}
		cout << "Median:[" << double(median) << "]" << endl;
	}

	_getche();

	return 0;
}
