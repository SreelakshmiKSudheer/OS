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
                int index = 0;
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
                       if(lastUse[j] < lastUse[index])
                                                index = j;
                }

                if(!found)
                {
                        faults++;
                        if(full())                      // frames is full
                        {
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

        lru(ref,n);
}

