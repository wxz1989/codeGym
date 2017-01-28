//Naive Pattern Matching Function
#include <stdio.h>

bool NaivePatternMatching( char source[], char pattern[], int sourceLength, int patternLength);

bool NaivePatternMatching(char source[], char pattern[], int sourceLength, int patternLength){
    int srcLen = sourceLength;
    int patLen = patternLength;

    for ( int i =0 ;i < srcLen ; i++){
        int index = i;
        for ( int j = 0 ; j<=patLen && (i+j)< srcLen ; j++){
          if ( source[index] != pattern[j]){
            index = i;
            break;
          } else {
            index++;

            if ( index == patLen ){
              return true;
            }
          }
        }
    }

    return false;
}


int main(){
  char array[] = "bacbabababacaca";
  char pattern[] = "ababaca";
  int strLen = 12;
  int pattLen = 3;

  printf("This is what:%d \n", NaivePatternMatching(array, pattern, strLen, pattLen));
  return 0;
}
