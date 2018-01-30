// A dynamic programming solution for longest palindr.
// This code is adopted from following link
// http://www.leetcode.com/2011/11/longest-palindromic-substring-part-i.html

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define MAX_SIZE 100
using namespace std;

int LPSBruteForce(char* str, int n, int& start, int& end){

	int maxLen = 0;

	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			if (str[i] == str[j]){
				int matchCount = 1;			
				for (int k = i + 1; k < j - 1; k++, matchCount++){
					if (str[k] == str[j - matchCount]){
						cout << "Matching :[" << str[k] << "] , End:[" << str[end - matchCount] << "]" << endl;
					} 
					else { break; }
				}
				if (matchCount > maxLen){
					maxLen = matchCount;
					start = i-1;
					end = j+1;
				}
			}
		}
	}
	return maxLen+2;
}
// A utility function to print a substring str[low..high]
void printSubStr(char* str, int low, int high)
{
	cout << "Start :[" << low << "] High:[" << high << "]" << endl;
	for (int i = low; i <= high; ++i)
		printf("%c", str[i]);
}

void PrintTable(bool table[][MAX_SIZE], int n){
	for (int k = 0; k <n; ++k)
	{
		for (int i = 0; i < n; ++i){
			cout << table[k][i] << " ";
		}
		cout << endl;
	}
}

// This function prints the longest palindrome substring
// of str[].
// It also returns the length of the longest palindrome
int longestPalSubstr(char *str)
{
	int n = strlen(str); // get length of input string

	// table[i][j] will be false if substring str[i..j]
	// is not palindrome.
	// Else table[i][j] will be true
	bool table[MAX_SIZE][MAX_SIZE];
	memset(table, 0, sizeof(table));

	// All substrings of length 1 are palindromes
	int maxLength = 1;
	for (int i = 0; i < n; ++i)
		table[i][i] = true;

	// check for sub-string of length 2.
	int start = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		if (str[i] == str[i + 1])
		{
			table[i][i + 1] = true;
			start = i;
			maxLength = 2;
		}
	}

	// Check for lengths greater than 2. k is length
	// of substring
	for (int k = 3; k <= n; ++k)
	{
		// Fix the starting index
		for (int i = 0; i < n - k + 1; ++i)
		{
			// Get the ending index of substring from
			// starting index i and length k
			int j = i + k - 1;

			// checking for sub-string from ith index to
			// jth index iff str[i+1] to str[j-1] is a
			// palindrome
			if (table[i + 1][j - 1] && str[i] == str[j])
			{
				table[i][j] = true;

				if (k > maxLength)
				{
					start = i;
					maxLength = k;
				}
			}
		}
	}
	PrintTable(table, n);

	printf("Longest palindrome substring is: ");
	printSubStr(str, start, start + maxLength - 1);

	return maxLength; // return length of LPS
}

// Driver program to test above functions
int main()
{
	char str[] = "forgeeksskeegfor";
	printf("nLength is: %dn", longestPalSubstr(str));

	int s = 0, e = 0;
	cout << "LPS Brute Force:" ;
	int len = LPSBruteForce(str, 15, s, e);
	cout << len << endl << "Start:[" << s << "] ,End :[" << e << "]" << endl;
	_getch();
	return 0;
}
