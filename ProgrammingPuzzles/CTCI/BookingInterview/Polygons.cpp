#include <iostream>
#include <stdio.h>

using namespace std;

int Sq=0, Rect=0, Others=0;
int values[10][4] = {0};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

	string line;

	int  i=0, j=0;
    while (std::cin >> values[i++][j++]){
    	if ( getchar() == 'e'){ break; }
	}	


	for ( int k =0; k<i;k++)
	{
		if ( values[k][0] == values[k][1] == values[k][2] == values[k][3]){
			Sq++;
		} else if (  values[k][0] == values[k][2] &&  values[k][1] == values[k][3]){
			Rect++;
		} else	{
			Others++;
		}	
	}
	cout << Sq << " " << Rect << " " << Others << endl;
	
	return 0;
}