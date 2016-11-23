#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#define MAX_TEST_CASE		30
#define MAX_QUEUE_SIZE		10000

using namespace std;

class Queue
{
public:
	Queue();
private:
	int size;
	int front;
	int rear;

	int queueArray[MAX_QUEUE_SIZE];
public:
	void add(int i);
	int getFront();
	int getRear();
	int getSize();
	bool isQueueEmpty();

	std::string getString();
};

std::string Queue::getString(){
	int index = 0;
	std::string retValue;
	retValue.append("[");
	char buffer[50];
	for (index = front; index < rear-1; index++){
		sprintf(buffer, "%d,", queueArray[index]);
		retValue.append(buffer);
	}
	sprintf(buffer, "%d]", queueArray[index]);
	retValue.append(buffer);
	return retValue;
}
int Queue::getSize(){
	return size;
}

Queue::Queue(){
	front = rear = 0;
	size = 0;
}

bool Queue::isQueueEmpty(){
	if (front == rear || size <= 0){ return true; }
	return false;
}

void Queue::add(int i){

	if (rear == MAX_QUEUE_SIZE){ return; }
	if (size >= MAX_QUEUE_SIZE){ return; }

	queueArray[rear++] = i;
	size++;
}
int Queue::getFront(){
	int val = 0;
	if (front >= 0 && front < rear){		//element int he middle.
		val = queueArray[front];
		queueArray[front++] = -1;
	}
	size--;
	return val;
}

int Queue::getRear(){
	int val = 0;
	if (front < rear){
		val = queueArray[--rear];
		queueArray[rear] = -1;
	}
	size--;
	return val;
}

int main(){

	Queue qu;

	srand(time(NULL));

	for (int i = 0; i < rand()%MAX_TEST_CASE; i++){
		qu.add(rand()%100);
	}
	cout << "Queued Elements:" << qu.getSize() << endl;
	cout << "Queue in String Form:" << qu.getString().c_str() << endl;
	qu.getFront();
	qu.getFront();
	qu.getFront();

	cout << "Queued Elements:" << qu.getSize() << endl;
	cout << "Queue in String Form:" << qu.getString().c_str() << endl;
	qu.add(rand()%100);
	qu.add(rand()%100);

	cout << "Queued Elements:" << qu.getSize() << endl;
	if (qu.getSize()>0){
		cout << "Queue in String Form:" << qu.getString().c_str() << endl;
		cout << "getRear: "<<endl;
		int index = 1;
		while (!qu.isQueueEmpty()){
			cout << "#" << index++ << " "<< qu.getRear() <<endl;
		}
		cout << "Queue in String Form:" << qu.getString().c_str() << endl;
	}
	return 0;
}