#include <stdio.h>

int main()
{
        int M,N;

        printf("How many types of resources are there? ");
        scanf("%d",&M);
        printf("How many no. of processes are there? ");
        scanf("%d",&N);

        const int n = N;
        const int m = M;

        int work[m], finish[n], max[n][m], available[m], allocation[n][m], need[n][m];
        int i,j;
        int safeSeries[n];

        // read maximum resources of each type required for each process
        for(i = 0; i < n; i++)
        {
                for(j = 0; j < m; j++)
                {
                        printf("Enter the maximum no. of resources of type %d required for process %d: ",j,i);
                        scanf("%d",&max[i][j]);
                }
        }

        // read no. of  resources of each type allocated for each process
        for(i = 0; i < n; i++)
        { 
                for(j = 0; j < m; j++)
                { 
                        printf("Enter the no. of resources of type %d that are currently allocated for process %d: ",j,i);
                        scanf("%d",&allocation[i][j]);

                        // need setting
                        need[i][j] = max[i][j] - allocation[i][j];
                }
        }

        // read no. resources of each type that are available 
        for(i = 0; i < m; i++)
        {
                printf("Enter the no. of resources of type %d that are available: ",i);
                scanf("%d",&available[i]);

                // work = available
                work[i] = available[i];
        }

        // finish set to 0
        for(i = 0; i < n; i++)
                finish[i] = 0;

        int count = 0,found;
        while(count < n)
        {
                found = 0;

                for(i = 0; i < n; i++)
                {

                        if(finish[i] == 0)
                        {
                                for(j = 0; j < m; j++)
                                {
                                        if(need[i][j] > work[j])
                                                break;
                                }
                                if(j == m)
                                {
                                        int k;
                                        for(k = 0; k < m; k++)
                                                work[k] += allocation[i][k];
                                        finish[i] = 1;
                                        safeSeries[count] = i;
                                        count++;
                                        found = 1;
                                }
                        }
                }

                if(found == 0)

                {
                        printf("System in unsafe state\n");
                        break;
                }
        }
        if(found == 1)
        {
                printf("System in safe state. \nSafe Sequence is:\n");
                for(i = 0; i < count; i++)
                {
                        printf("P%d ",safeSeries[i]);
                }
                printf("\n");
        }


}


