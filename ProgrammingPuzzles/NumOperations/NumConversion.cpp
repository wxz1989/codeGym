#include <iostream>

using namespace std;

void Test_RandomisedDataInput(int No, int array[], bool choice);

int ConvertToNum(int arr[], int length){
	if (length <= 0){
		return -1;
	}

	int No =0;
	int index = 0;

	while(index < length){
		if ( No <=0 ){
			No = arr[index];
		} else {
			No = (No*10) + arr[index];
		}
		index++;
	}
	return No;
}

bool ExtractNo(int No, int arr[], int arrLength){
	if ( No <=0 || arrLength <=0 ){
		return false;
	}
	int temp = No;
	int index = 0;
	while ( temp >0 ){
		int digit = temp %10;
		temp = temp /10;

		arr[arrLength-(++index)] = digit;
	}
	return true;
}

void Test_RandomisedDataInput(bool choice = false){

	srand(time(NULL));
	int inputSize = rand() % 50;
	srand(time(NULL));

	int arrRep[10] = {0};

	for (int i = 0; i< inputSize; i++){
		int value = rand() % 99999;

		int temp = value;
		int length = 0;
		while ( temp > 0 ){
			temp = temp /10;
			length++;
		}
		cout << "Original No [" << value <<"]: ";
		ExtractNo(value, arrRep, length);


		for(int i = 0; i < length;i++){
			cout << arrRep[i] << " ";
		}
		cout << endl;

		cout <<"Converting it back to No: [" << ConvertToNum(arrRep, length) << "]" <<  endl; 
	}
}


int main(int argc, char* argv[]){

	Test_RandomisedDataInput();
	return 0;
}