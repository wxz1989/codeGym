//
//  main.cpp
//  WaterJugProblem
//
//  Created by Rakesh Gajjar on 3/20/13.
//  Copyright (c) 2013 Rakesh Gajjar. All rights reserved.
//

#include <iostream>
#include <string.h>


#define MAX_JUG_CAPACITY 50

static int capacity[2];
static int current[2];
static int required;

#define MAX_PENALTY 1

int DataSet1[] = {2,4,6,8,3};
int DataSet2[] = {2,3,4,5,6,7,8,9,10,1};
int DataSet3[] = {6,5,3,1,8,7,2,4};
int DataSet4[] = {3,5,6,8,9,2};
int DataSet5[] = {2,3,4,5,6,7,8,9,10,-1};
int DataSet6[] = {-10,-1,2,4,6,8,9,10,12,-20};
int DataSet7[] = {-10,-1,2,4,6,8,9,10,12,0};
int DataSet8[] = {1,4,3,5,6,2};

static int penalty;
static int number_of_moves;

void insertionSort(int ar_size, int *  ar) ;
void insertionSortUnSorted(int ar_size, int *  ar);
void PrintArray(int ar_size, int *array);

int do_the_jugglery(int cap1, int cap2, int out);

void move ( int a, int b);

void empty(int j);
void fill ( int j );
void output(int j);

static void internal_int(int c1, int c2, int out){
    capacity[0]= c1;
    capacity[1] = c2;
    
    current[0] = current[1] = 0;
    
    penalty = 0;
    number_of_moves =0;
    required =out;
}

void move(int A, int B){
    int min_value;
    int remaining_B;
    
    remaining_B = capacity[B] - current[B];
    
    if ( remaining_B < current[A])
        min_value = remaining_B;
    else
        min_value = current[A];
    
    current[A]-= min_value;
    current[B] +=min_value;
    
    number_of_moves++;
}

void empty(int j)
{
    current[j] =0;
    number_of_moves++;
}

void fill(int j)
{
    current[j] = capacity[j];
    number_of_moves++;
}

void output(int j)
{
    if (required != current[j]){
        penalty += MAX_PENALTY;
    }
}

char is_pass, is_senior, is_fail,is_expert;

#define NUM_EXAMPLES 10

int input_A[NUM_EXAMPLES] = {2,6,9,12,16,21,31,47,22,26};
int input_B[NUM_EXAMPLES] = {10,7,17,41,31,31,33,49,37,35};
int output_C[NUM_EXAMPLES] = {9,5,11,13,7,11,26,26,7,19};

int
main(int argc, const char * argv[])
{
    // insert code here...
    int a,b,c,ret,i;
    int nm;
    char outstr[1000];
    
    is_pass = is_senior = is_fail = is_expert = 0;
    
    for (i = 0; i<NUM_EXAMPLES; i++)
    {
        a = input_A[i];
        b = input_B[i];
        c = output_C[i];
        
        internal_int(a,b,c);
        ret = do_the_jugglery(a,b,c);
        nm = number_of_moves;
        
        output(ret);
        
        if ( penalty ){
            printf("you have output a wrong jug number in %d moves! \n", nm);
            is_pass = 0;
        }
        else
        {
            printf("you have output a correct jug number in [%d] moves! \n", nm);
            is_pass = 1;
        }
    }
    
    
    outstr[0]='\0';
    
    if ( is_pass )
    {
        strcat(outstr, "PASS ");
        if ( is_senior )
        {
            strcat(outstr, "SENIOR ");
            if ( is_expert )
            {
                strcat(outstr, "EXPERT ");
            }
        }
    }
    else
        strcat(outstr, "FAIL ");
   
     printf("%s\n", outstr);
    
    //    printf("\n Calling Sorting functions!");
    //    //insertionSort(5, DataSet8);
    printf("\nInput Array\n");
    PrintArray(6, DataSet8);
    printf("Sorted Array\n");
    insertionSortUnSorted(6,DataSet8);
    //    printf("\n Insertion Sort Done!");
    
    return 0;
}

void PrintArray(int ar_size, int *array)
{
    for ( int i = 0; i < ar_size ; i++)
        printf("%d ", array[i]);
    printf("\n");
}
void insertionSort(int ar_size, int *  ar)
{
    int Key =0;
    
    if ( ar_size ==0 || ar == NULL )
        return;

    printf("\n");
#if 1 //This aproach solves problem from top to bottom ( from last element of the sorted array to first)
    Key = ar[ar_size-1];
    if( Key > ar[ar_size-2])
    {
        PrintArray(ar_size, ar);
        return;
    }
    for ( int i = ar_size-2; i >= 0 ; i--)
    {
        if ( ar[i] > Key)
        {
            if ( i == 0 )
            {
                ar[i+1] = ar[i];
                PrintArray(ar_size, ar);
                ar[i] = Key;
            }
            else
                ar[i+1] = ar[i];
        }
        else
        {
            ar[i+1] =Key;
            PrintArray(ar_size,ar);
            return;
        }
        PrintArray(ar_size, ar);
    }
#else               //As per algorithm given in the book, the code goes like this.
    int j = 0 ;
    
    for ( int i = 0 ; i < ar_size-1; i++)
    {
        Key = ar[i];
        j = i;
        
        printf("\n Print Swaping List Key[%d]", Key);
        while ( j > 0 &&  Key < ar[j - 1])
        {
            ar[j] = ar[j-1];
            j--;
            PrintArray(ar_size, ar);
        }
        ar[j] = Key;
        PrintArray(ar_size, ar);
    }
#endif
}

void insertionSortUnSorted(int ar_size, int *  ar)
{
    int Key =0, iTemp=0;
    bool bMovedToPosition = false;
    for ( int j =0; j< ar_size; j++)
    {
        bMovedToPosition = false;
        for ( int i = ar_size-1; i>  0 ; i--)
        {
            Key = ar[i];
            if( Key > ar[i-1])
            {
                if( bMovedToPosition == true )
                    PrintArray(ar_size, ar);
                continue;
            }
            else
            {
                bMovedToPosition = true;
                iTemp = ar[i-1];
                ar[i-1] = Key;
                ar[i] = iTemp;
            }
        }
    }

}