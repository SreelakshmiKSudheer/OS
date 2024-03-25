#include <stdio.h>

typedef struct Process
{
    int PID;
    int arr_time;
    int burst_time;
    int ta_time;
    int resp_time;
    int comp_time;
    int wait_time;

}Process;

void sort(Process *a, int n)
{
    int i,j;
    Process temp;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(a[j].arr_time > a[j+1].arr_time)
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;

            }
        }
    }
}

void fcfs(Process *a, int n)
{
    sort(a,n);

    int i;
    printf("First Come First Serve\n");
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int start = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0;

    for(i = 0; i < n; i++)
    {
        if(start < a[i].arr_time)
        {
            start = a[i].arr_time;
        }

        a[i].resp_time = start - a[i].arr_time;
        a[i].comp_time = start + a[i].burst_time;
        a[i].ta_time = a[i].comp_time - a[i].arr_time;
        a[i].wait_time = a[i].burst_time;

        printf("%2d%15d%12d%15d%17d%18d%14d",a[i].PID,a[i].arr_time,a[i].burst_time,a[i].resp_time,a[i].comp_time,a[i].ta_time,a[i].wait_time);

        start = a[i].comp_time;

        resp_sum += a[i].resp_time;
        ta_sum += a[i].ta_time;
        wait_sum += a[i].wait_time;

    }

    printf("\nAvg response time: %.2f",(float)resp_sum/n);
    printf("\nAvg turn around time: %.2f",(float)ta_sum/n);
    printf("\nAvg waiting time: %.2f",(float)wait_sum/n);
    
}
int main()
{
    int n,i;

    printf("How many process? ");
    scanf("%d",&n);

    int const N = n;
    Process a[N];

    printf("Enter processes in the following specified format:\n");

    for(i = 0; i < n; i++)
    {
        printf("Process ID: ");
        scanf("%d",&a[i].PID);
        printf("Arrival Time: ");
        scanf("%d",&a[i].arr_time);
        printf("Burst Time: ");
        scanf("%d",&a[i].burst_time);
    }

    fcfs(a,n);
}