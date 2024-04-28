#include <stdio.h>
#include <math.h>

void fcfs(int r[],int n,int head)
{
    int i,seek_sum = 0;

    printf("\n\nFCFS\n");
    printf("Accessing order of data: \n");
    for(i = 0; i < n; i++)
    {
        printf("%d ",r[i]);
        seek_sum += abs(head - r[i]);
        head = r[i];
    }
    printf("\nTotal seek time: %d",seek_sum);
    printf("\nAvg seek time: %.2f\n\n",(float)seek_sum/n);
}

int main()
{
    int N,i,head;

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

    fcfs(r,n,head);

}