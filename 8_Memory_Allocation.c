#include <stdio.h>

#define SIZE 5

int partition[SIZE] = {600,320,245,125,575};

void display(int external,int internal,int rec[],int order[])
{
        int i;

        printf("Memory Allocation:\n");
        for(i = 0; i < SIZE; i++)
        {
                if(rec[i] != 0)
                        printf("%d KB partition is allocated to process P%d\n", partition[i],order[i]);
        }

        if(internal == 0 && external == 0)
                printf("No fragmentation\n");
        else if(internal != 0 && external == 0)
        {
                printf("Memory wastage due to internal fragmentation: %d\n",internal);
                printf("No external fragmentation\n");
        }
        else if(internal == 0 && external != 0)
        {
                printf("Memory wastage due to external fragmentation: %d\n",external);
                printf("No internal fragmentation\n");
        }
        else
        {
                printf("Memory wastage due to internal fragmentation: %d\n",internal);
                printf("Memory wastage due to external fragmentation: %d\n",external);

        }

        printf("\n----------------------------------------------------------\n");
}

void ff(int mr[],int N)
{
        int internal = 0, external = 0;
        const int n = N;
        int i, j, rec[SIZE], order[n];

        for(i = 0; i < SIZE; i++)
                rec[i] = 0;

        for(i = 0; i < n; i++)
        {
                for(j = 0; j < SIZE; j++)
                {
                        if(rec[j] == 0 && mr[i] <= partition[j])
                        {
                                rec[j] = 1;
                                order[j] = i;
                                internal += partition[j] - mr[i];
                                break;
                        }
                }
        }

        for(i = 0; i < SIZE; i++)
        {
                if(rec[i] == 0)
                        external += partition[i];
        }

        printf("\nFirst Fit\n");
        display(external,internal,rec,order);
        
}

void bf(int mr[],int N)
{
        int internal = 0, external = 0,min;

        const int n = N;
        int i, j, rec[SIZE], order[n];

        for(i = 0; i < SIZE; i++)
        {
                rec[i] = 0;
                //order[i] = 0;
        }
        for(i = 0; i < n; i++)
        {
                min = -1;

                for(j = 0; j < SIZE; j++)
                {
                        if(rec[j] == 0 && mr[i] <= partition[j])
                        {
                                if(partition[j] < partition[min] || min == -1)
                                        min = j;

                        }
                }
                rec[min] = 1;
                order[min] = i;
                internal += partition[min] - mr[i];

        }

        for(i = 0; i < SIZE; i++)
        {
                if(rec[i] == 0)
                        external += partition[i];
        }

        printf("\nBest Fit\n");
        display(external,internal,rec,order);

}

void wf(int mr[],int N)
{
        int internal = 0, external = 0,index;

        const int n = N;
        int i, j, rec[SIZE], order[n];

        for(i = 0; i < SIZE; i++)
        {
                rec[i] = 0;
                //order[i] = 0;
        }
        for(i = 0; i < n; i++)
        {
                index = -1;

                for(j = 0; j < SIZE; j++)
                {
                        if(rec[j] == 0 && mr[i] <= partition[j])
                        {
                                if(partition[j] > partition[index] || index == -1)
                                        index = j;

                        }
                }
                rec[index] = 1;
                order[index] = i;
                internal += partition[index] - mr[i];

        }

        for(i = 0; i < SIZE; i++)
        {
                if(rec[i] == 0)
                        external += partition[i];
        }

        printf("\nBest Fit\n");
        display(external,internal,rec,order);

}
          
int main()
{
        int i,N;
        printf("Memory partition is given below:\n| ");

        for(i = 0; i < SIZE; i++)
                printf("%8d KB| ",partition[i]);
        printf("\n");

        printf("How many processes? ");
        scanf("%d",&N);

        const int n = N;
        int mr[n];

        printf("Enter the memory requirements of each process: \n");

        for(i = 0; i < n; i++)
                scanf("%d",&mr[i]);

        ff(mr,n);
        bf(mr,n);
        wf(mr,n);
}