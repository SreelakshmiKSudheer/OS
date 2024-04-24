#include <stdio.h>

#define SIZE 3

int isfull(int front,int rear)
{
    if(front == (rear + 1 ) % SIZE)
        return 1;
    else    
        return 0;
}

int isempty(int front,int rear)
{
    if(front == -1 && rear == -1)
        return 1;
    return 0;
}

void enqueue(int pf[],int *front,int *rear,int item)
{
    if(*front == -1)
        *front = 0;
    *rear = (*rear + 1) % SIZE;
    pf[*rear] = item;
}

int dequeue(int pf[],int *front,int *rear)
{
    int item = pf[*front];
    *front = (*front + 1) % SIZE;
    if(*front == (*rear + 1) % SIZE)
        *front = *rear = -1;
    return item;
}

void display(int pf[], int front, int rear)
{
    int i = front;

    while(i != rear)
    {
        printf("%d ",pf[i]);
        i = (i + 1) % SIZE;
    }
    printf("%d\n", pf[rear]);
}

void fifo(int ref[],int n)
{
    int front = -1, rear = -1;
    int pf[SIZE],found,i,j,fault = 0;

    printf("First In First Out\n");
    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < SIZE; j++)
        {
            if(ref[i] == pf[j])             // page found
            {
                found = 1;
                break;
            }
        }

        if(found == 0)                      // page not found
        {
            fault++;
            if(!isfull(front,rear))
            {
                enqueue(pf,&front,&rear,ref[i]);
            }
            else
            {
                dequeue(pf,&front,&rear);
                enqueue(pf,&front,&rear,ref[i]);
            }
        }

        printf("%d :\t",ref[i]);
        display(pf,front,rear);

    }
    printf("Page faults: %d\n",fault);
}

int search(int pf[], int front, int rear,int current, int ref[],int n)
{
    int i,j;

    for(i = front; i != rear; i = (i + 1) % SIZE)
    {
        for(j = current + 1; j < n; j++)
        {
            if(pf[i] == ref[j])
                return j;

        }
    }
    
}

void optimal(int ref[],int n)
{
    int front = -1, rear = -1;
    int pf[SIZE],found,i,j,k,fault = 0;

    printf("Optimal Replacement\n");
    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < SIZE; j++)
        {
            if(ref[i] == pf[j])             // page found
            {
                found = 1;
                break;
            }
        }

        if(found == 0)                      // page not found
        {
            fault++;
            if(!isfull(front,rear))
            {
                enqueue(pf,&front,&rear,ref[i]);
            }
            else
            {
                
                dequeue(pf,&front,&rear);
                enqueue(pf,&front,&rear,ref[i]);
            }
        }

        printf("%d :\t",ref[i]);
        display(pf,front,rear);

    }
    printf("Page faults: %d\n",fault);
}

int main()
{
    int N;

    printf("Enter no. of processes? ");
    scanf("%d",&N);

    const int n = N;

    int ref[n],i;

    printf("Enter the reference string:\n");

    for(i = 0; i < n; i++)
        scanf("%d",&ref[i]);

    
    fifo(ref,n);
    optimal(ref,n);
    //lru(ref,n);
    //lfu(ref,n);
    //mfu(ref,n);
}