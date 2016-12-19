#include <iostream>

using namespace std;

int ToNum(char* pC, int len){

	bool negative = false;
	int Ans = 0;
	if (pC == NULL || len == 0 ){ return -1;}

	int i = 0;
	if( pC[0] == '-'){
		negative = true;
		i = 1;
	}
	for (; i< len; i++){
		int No = abs(pC[i] - '0');
		if ( No >=0 && No <=9){
			if ( Ans == 0 ){
				Ans = No;
			} else{
				Ans *= 10;
				Ans += No;
			}
		} else{
			Ans = -1;
			break;
		}
	} 
	if( negative ){
		Ans *= -1;
	}
	return Ans;
}
/*You are required to complete this method */
int atoi(string str)
{
	char* pChar = NULL;
	int len = 0;


	pChar = (char*)str.c_str();
	len = str.length();
	int No = ToNum(pChar, len);
	return No;
    //Your code here
}


int main(){
	std::string inputStr="-1";
	cout <<"ATOI:"<< atoi(inputStr)<<endl;	
}