#include <stdio.h>
#include <math.h>

void sort(int *r, int n)
{
    int i,j;                    // loop variables
    int temp;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(r[j] > r[j+1])
            {
                temp = r[j];
                r[j] = r[j+1];
                r[j+1] = temp;

            }
        }
    }
}

void cscan(int r[],int n,int head,int limit)
{
    int i,seek_sum = 0,index = 0;
    sort(r,n);

    printf("\n\nC-SCAN\n");
    printf("Accessing order of data: \n");
    
    seek_sum += abs(limit - head);
    seek_sum += limit;

    for(i = 0; i < n; i++)
    {
        if(r[i] < head)
            continue;
        index++;
        printf("%d ",r[i]);
        
    }
    index = n - index;
    seek_sum += r[index - 1];

    for(i = 0; i < index; i++)
    {
        printf("%d ",r[i]);
    }

    printf("\nTotal seek time: %d",seek_sum);
    printf("\nAvg seek time: %.2f\n\n",(float)seek_sum/n);
}

int main()
{
    int N,i,head,limit;

    printf("Enter the no. of requests: ");
    scanf("%d",&N);

    const int n = N;
    int r[n];
    printf("Enter the positions of the requested data: \n");

    for(i = 0; i < n; i++)
    {
        scanf("%d",&r[i]);
    }

    printf("Enter the current position of disk head: ");
    scanf("%d",&head);
    printf("Enter the limit disk head: ");
    scanf("%d",&limit);

    scan(r,n,head,limit);
    cscan(r,n,head,limit);

}