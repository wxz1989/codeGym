//
//  rakesh.2206.cpp
//  WaterJugProblem
//
//  Created by Rakesh Gajjar on 3/20/13.
//  Copyright (c) 2013 Rakesh Gajjar. All rights reserved.
//

#include "rakesh.2206.h"

#define BOARD_SIZE 4


int Board[BOARD_SIZE][BOARD_SIZE] ={{},{},{},{}};
bool PossiblePlacement[BOARD_SIZE][BOARD_SIZE] = {{},{},{},{}};

bool FindPlace(int iRow, int iCol);

#define MAX_JUG_CAPACITY 50
int do_the_jugglery(int cap1, int cap2, int out);

void fill ( int j );
void move(int A, int B);
void empty(int j);
int output(int j );
void SetRemainingCapacity(bool bMoveDir=true);
int GCD(int x, int y);

static int iCurrCapA,  iCurrCapB, iMaxCapA, iMaxCapB;

int GCD(int x, int y)
{
    if (y == 0)
        return x;
    else
        return GCD(y, x % y);
}

int do_the_jugglery(int cap1, int cap2, int out){
    
    const int a = 0;
    const int b = 1;
    int gcdValue =0;
    
    
    //Very IMPORTANT and CRITICAL condition here to be ked before doing any calculation is:
    //Note: The out(volumn of the output) must be a multiple of GCD(A,B) else there is no solution.(Critical for passing expert level)
    //If GCD(A,B) == 1, There is a solution for Any Q. (Anything can be reproduced for output.
    
    gcdValue = GCD(cap1, cap2);
    
    printf("GCD of [%d] [%d] is [%d]", cap1, cap2, gcdValue);
    
    if ( (out  % gcdValue ==0 ) || gcdValue ==1)
        printf(" Solution possible\n");
    else
    {
        printf("Solution not possible\n");
        return -1;
    }
    
    int diff = 0;
    
    iMaxCapA = cap1;
    iMaxCapB = cap2;
    
    if ( cap1 == 0 || cap1 == out)
    {
        fill(a);
        return a;
    }
    if ( cap2 ==0 || cap2 == out){
        fill(b);
        return b;
    }
    
    if ( cap1 > cap2)
        diff = cap1 - cap2;
    else
        diff = cap2- cap1;
 
    //First condition which needs to be evaluated everytime.
    fill(b);
    iCurrCapB = cap2;
    
    do {
        move(b,a);
        SetRemainingCapacity();
        //if b reaches maximum quatity of jug then empty jug.
        //if jug a becomes empty then refill it.
        if ( iCurrCapA == cap1)
        {
            empty(a);
            iCurrCapA = 0;
        }
        if ( iCurrCapB == 0 )
        {
            fill(b);
            iCurrCapB = cap2;
        }
    
        if ( iCurrCapA == out)
            return a;
        else if ( iCurrCapB == out)
            return b;
        else
            continue;
        
    } while (1);
    return 0;
}


void SetRemainingCapacity(bool bMoveDir)
{
    int iTemp = 0;
    if ( bMoveDir == true)          //Move form B to A (as per current scenario, movement from b to a is cosidered.
    {
        if ( iCurrCapA + iCurrCapB == iMaxCapA)
        {
            iCurrCapA = iMaxCapA;
            iCurrCapB =0;
        }
        else if ( iCurrCapA + iCurrCapB > iMaxCapA)
        {
            iTemp = iMaxCapA - iCurrCapA;
            iCurrCapA += iTemp;
            iCurrCapB -=iTemp;
        }
        else
        {
            iCurrCapA += iCurrCapB;
            iCurrCapB -= iCurrCapB;
        }
    }
    else
    {
        
    }
}
//End of Code

bool FindPlace(int iRow, int iCol)
{
    for ( int i = 0; i< BOARD_SIZE ; i++)
    {
        if ( iRow == i )                                    //Queens can't be placed in same row.
            return false;
        for ( int j = 0; j< BOARD_SIZE; j++)
        {
            if ( PossiblePlacement[i][j] == true)            //place alreacy occupied
                return false;
            else if ( iCol== j )                            //Queens can't be placed in same column.
                return false;
            else if ( iRow-i == iCol-j)                        //Queens can't be placed diagonally as they will be in attacking situation in this condition.
                return false;
            else
            {
                PossiblePlacement[i][j] = true;
                return true;                                //Only case when possible position can be found.
            }
        }
    }
    return false;
}

