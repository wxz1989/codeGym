
#include <stdio.h>

int main(){

	int testCases = 0 , begin = 0, N = 0;
	scanf("%d", &testCases);
	scanf("%d %d", &begin, &N);

	//printf("\n");
	for (int i = 1; i <= N ; i++)
	{
		/* code */
		if ( i % 3 == 0 && i % 5 == 0 ){ printf("FizzBuzz\n"); } 
		else if ( i % 3 == 0 ){ printf("Fizz\n"); }
		else if ( i % 5 == 0 ) { printf("Buzz\n"); }
		else { printf( "%d\n", i); }
	}
}