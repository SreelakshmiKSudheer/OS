#include <stdio.h>

#define MAX 3
#define NILL -99999999

int frame[MAX];

void initialize()
{
        int i;
        for(i = 0; i < MAX; i++)
                frame[i] = NILL;
}

int full()
{
        int i;
        for(i = 0; i < MAX; i++)
        {
                if(frame[i] == NILL)
                        return 0;
        }

        return 1;
}

void display(int found)
{
        int j;

        for(j = 0; j < MAX; j++)
        {
                if(found)
                        break; 
                if(frame[j] == NILL)
                        printf(" ");
                else
                       printf("%d ",frame[j]);
        }
        printf("\n");


}

void fifo(int ref[],int n)
{
        int front = -1,rear = -1,i,j, faults = 0,current,found;

        initialize();


        printf("\n\nFIFO\n");
        for(i = 0; i < n; i++)
        {
                current = ref[i];
                found = 0;

                for(j = 0; j < MAX; j++)
                {
                        if(frame[j] == current)
                        {
                                found = 1;
                                break;
                        }
                }

                if(!found)
                {
                        faults++;
                        if(front == (rear+1) % MAX)
                        {
                                front = (front+1) % MAX;                // dequeue
                                rear = (rear+1) % MAX;                  // enqueue
                                frame[rear] = current;
                        }
                        else
                        {
                                rear = (rear+1) % MAX;                  // enqueue
                                frame[rear] = current;
                        }
                }
                printf("%d : \t",current);
                display(found);

        }

        printf("No. of page faults : %d\n\n",faults);
}

void lru(int ref[],int n)
{
        int front = -1,rear = -1,i,j, faults = 0,current,found;
        int lastUse[MAX];

        for(i = 0; i < MAX; i++)
                lastUse[i] = -1;

        initialize();

        printf("\n\nLRU\n");
        for(i = 0; i < n; i++)
        {
                current = ref[i];
                found = 0;

                for(j = 0; j < MAX; j++)
                {
                        if(frame[j] == current)
                        {
                                found = 1;
                                lastUse[j] = i;
                                break;
                       }
                }

                if(!found)
                {
                        faults++;
                        if(full())                      // frames is full
                        {

                               int index = 0;
                                int k;
                                for(k = 1; k < MAX; k++)
                                {
                                        if(lastUse[k] < lastUse[index])
                                                index = k;
                                }
                                frame[index] = current;
                                lastUse[index] = i;
                        }
                        else                                            // frames not full
                        {
                                rear = (rear+1) % MAX;                  // enqueue
                                frame[rear] = current;
                                lastUse[rear] = i;

                        }

               }
                printf("%d : \t",current);
                display(found);

        }
        printf("No. of page faults : %d\n\n",faults);
}

void lru(int ref[],int n)
{
        int front = -1,rear = -1,i,j, faults = 0,current,found;
        int lastUse[MAX];

        for(i = 0; i < MAX; i++)
                lastUse[i] = -1;

        initialize();

        printf("\n\nLRU\n");
        for(i = 0; i < n; i++)
        {
                current = ref[i];
                found = 0;

                for(j = 0; j < MAX; j++)
                {
                        if(frame[j] == current)
                        {
                                found = 1;
                                lastUse[j] = i;
                                break;
                       }
                }


               if(!found)
                {
                        faults++;
                        if(full())                      // frames is full
                        {

                                int index = 0;
                                int k;
                                for(k = 1; k < MAX; k++)
                                {
                                        if(lastUse[k] < lastUse[index])
                                                index = k;
                                }
                                frame[index] = current;
                                lastUse[index] = i;
                        }
                        else 
                       {
                                rear = (rear+1) % MAX;                  // enqueue
                                frame[rear] = current;
                                lastUse[rear] = i;

                        }

                }
                printf("%d : \t",current);
                display(found);

        }
        printf("No. of page faults : %d\n\n",faults);
}

int main()
{
        int N,i;

        printf("How many pages in reference string: ");
        scanf("%d", &N);

        const int n = N;
        int ref[n];

        // read reference string 
        printf("Enter the reference string: \n");
        for(i = 0; i < n; i++)
        {
                scanf(" %d",&ref[i]);
        }

        fifo(ref,n);
        lru(ref,n);
        //lfu(ref,n);
}

