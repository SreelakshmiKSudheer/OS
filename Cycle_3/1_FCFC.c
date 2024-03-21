#include <stdio.h>

typedef struct Process
{
    char PID[3];
    int Arr_time;
    int Burst_time;
    int TA_time;
    int Resp_time;
    int W8_time;

}Process;

void Sort(Process *a, int n)
{
    int i,j;
    Process temp;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n-i-1; j++)
        {
            if(a[j].Arr_time > a[j+1].Arr_time)
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
    Sort(a,n);

    int i;
    printf("First Come First Serve\n");
    printf("PID\tArrival Time\tBurst Time\tResponse Time\tCompletion Time\t\tTurn Around Time\tWaitin Time\n");

    int start = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0;

    for(i = 0; i < n; i++)
    {
        if(start < a[i].Arr_time)
        {
            start = a[i].Arr_time;
        }
    }
}
int main()
{
    int n;

    printf("How many process? ");
    scanf("%d",&n);


}