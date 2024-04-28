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

int allcompleted(int rec[],int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(rec[i] == 0)
            return 0;
    }
    return 1;
}

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

void sstf(int r[],int n,int head)
{
    int i,seek_sum = 0,min = -1;
    const int N = n;
    int rec[N];

    for(i = 0; i < n; i++)
    {
        rec[i] = 0;
    }

    sort(r,n);

    printf("\n\nSSTF\n");
    printf("Accessing order of data: \n");
    
    while(!(allcompleted(rec,n)))
    {
        min = -1;
        for(i = 0; i < n; i++)
        {
            if(rec[i] == 0)
            {
                if(abs(head - r[i]) < abs(head - r[min]) || min == -1)
                    min = i;
            }
        }
        printf("%d ",r[min]);
        seek_sum += abs(head - r[min]);
        head = r[min];
        rec[min] = 1;
    
    }
    
    printf("\nTotal seek time: %d",seek_sum);
    printf("\nAvg seek time: %.2f\n\n",(float)seek_sum/n);
}

void scan(int r[],int n,int head,int limit)
{
    int i,seek_sum = 0,index = 0;
    sort(r,n);

    printf("\n\nSSTF\n");
    printf("Accessing order of data: \n");
    
    seek_sum += abs(limit - head);
    seek_sum += abs(limit - r[0]);

    for(i = 0; i < n; i++)
    {
        if(r[i] < head)
            continue;
        index++;
        printf("%d ",r[i]);
        
    }
    index = n - index;

    for(i = index-1 ; i >= 0; i--)
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

    fcfs(r,n,head);
    sstf(r,n,head);
    scan(r,n,head,limit);
    //cscan(r,n,head,limit);
    //look(r,n,head);
    //clook(r,n,head);

}