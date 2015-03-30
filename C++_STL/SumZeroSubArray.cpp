
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <map>

#include "main.h"

using namespace std

bool SumZeroSubArray(int array[],  int arraySize,int& startIndex, int& endIndex);


/*	There is another way for doing the same.
	Take a hash map and keep adding number form o to the item index. Keep Sum as a Key in the map and values as the index of it in the main array.
	 Once done verify following rules to make sure there is answer...
1. Find elements with same keys. (if there are elements whose keys (Sums) are same then there must SumZero SubArray. To find them, find first element with sum. Find it's index + 1th element in the main arrat up to the next same sum element and that would be a SumZero SubArray.
2. Find element whose sum(key) is zero, sum up to items from 0 to that index of main arrat and that is another Sum Zero SubArray. 

*/
bool SumZeroSubArray(int array[],  int arraySize,int& startIndex, int& endIndex)
{
	bool bRet = false;
	int sum = 0;

	//Check for the validity of given arguments...
	//1st Array...

	int test = sizeof(array)/sizeof(array[0]);
	cout<<"Calculated ArraySize: "<<test<<endl;

	if ( arraySize == 0 )
	{
		std::cout<<"Array is empty";
		return bRet;
	}

	for ( int i = 0; i< arraySize; i++)
	{
		sum = array[i];

		if ( array[i] == 0 )
		{
			startIndex = endIndex = i;
			bRet = true;
			return bRet;
		}

		for ( int j = i+1; j < arraySize; j++)
		{
			sum += array[j];
			if ( array[j] == 0 )
			{
				startIndex = endIndex = j;
				bRet = true;
				return bRet;
			}

			if ( sum == 0 )
			{
				startIndex = i;
				endIndex = j;
				bRet = true;
				return bRet;
			}
		}
	}

	return bRet;
}


void main()
{
	//Test for SumZeroSubArray...
	int start=0, end = 0;
	//int arr[] =  {4, 2, -3, 1, 6};
	int arr[] = {4,  6,  3, -9, -5, 1, 3, 0, 2};

	if ( SumZeroSubArray(arr,9, start, end)) {
		std::cout<<"SubZero SubArray Found at Start["<<start<<"]...End[["<<end<<"] indices!!!"<<endl;
	}
	else { 
		std::cout<<"SubZero SubArray Not Found!!!"; 
	}


	getchar();
	return;
}
