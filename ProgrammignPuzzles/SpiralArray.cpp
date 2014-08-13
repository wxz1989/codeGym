//Programming Puzzle : Print the given arrat in Spiral order
#include <iostream>
using namespace std;

void PrintSpiral(int M[4][4],int N,int K)
{

    int left = 0,right = K-1,top = 0,bottom = N-1,i;
    while(1)
    {
        if(left > right || top > bottom)
            break;
        for(i = left ; i <= right ; i++)
            cout<<" "<<M[top][i];
        top++;
        if(left > right || top > bottom)
            break;
        for(i = top ; i <= bottom ; i++)
            cout<<" "<<M[i][right];
        right--;
        if(left > right || top > bottom)
            break;
        for(i = right ; i >= left ; i--)
            cout<<" "<<M[bottom][i];
        bottom--;
        if(left > right || top > bottom)
            break;
        for(i = bottom ; i >= top ; i--)
            cout<<" "<<M[i][left];
        left++;
    }
}

int main(void)
{
    int M[4][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    PrintSpiral(M,4,4);
    return 0;
}
