#include <stdio.h>

int main()
{
    int M,N;

    printf("How many processes? ");
    scanf("%d",&N);
    printf("How many types of resources? ");
    scanf("%d",&M);

    const int m = M;
    const int n = N;

    int work[m],finish[n],available[m],allocation[n][m],max[n][m],need[n][m];
    int safeseq[n];
    int i,j;

    // max read
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("Enter the maximum no. of resources of type %d are required for the process %d:  ",j,i);
            scanf("%d",&max[i][j]);
        }
    }

    // set allocation, need
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            // allocation
            printf("Enter the no. of resources of type %d that are allocated to the process %d:  ",j,i);
            scanf("%d",&allocation[i][j]);

            // need
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // available
    for(j = 0; j < m; j++)
    {
        printf("Enter the no. of resources of type %d are available:  ",j);
        scanf("%d",&available[j]);

        // initialized work
        work[j] = available[j];
    }

    // finish set to false
    for(i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n)
    {
        int suit = 0;

        for(i = 0; i < n; i++)
        
        {
            for(j = 0; j < m; j++)
            {
                
            }
        }
    }
    
}   