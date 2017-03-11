#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define  MAX_VALUES  100
int arrayValue[MAX_VALUES] = {0};
int temp[MAX_VALUES] = {0};

using namespace std;
int main() {

	int  count = 0;
    while (std::cin >> arrayValue[count]){
    	count++;
    	if ( getchar() == '\n'){ break; }
	}	

	temp[0] = arrayValue[0];
	for( int i = 1 ;i < count;i++){
		temp[i] =  arrayValue[i] - arrayValue[i-1];
	}
	for( int i = 0 ;i < count;i++){

		if( i == 0 ){ cout << temp[0] <<" "; }
		else{
			if (temp[i]< -127 || temp[i] > 127) { cout << -128 << " " ;}
			cout << temp[i] << " " ;
		}
	}
    return 0;
}