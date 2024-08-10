#include <stdio.h>

typedef struct Process
{
    int PID;
    int arr_time;
    int burst_time;
    int start;
    int ta_time;
    int resp_time;
    int comp_time;
    int wait_time;
    int priority;
    int remain;

}Process;

// sort according to arrival time
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

// print details in acsending order of arrival time
void print(Process *a, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%2d%15d%12d %d %15d%17d%18d%14d\n",a[i].PID,a[i].arr_time,a[i].burst_time,a[i].start,a[i].resp_time,a[i].comp_time,a[i].ta_time,a[i].wait_time);

    }
}

// check whether all processes are completed or not at once
int allCompleted(int n,int rec[])
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(rec[i] == 0)
            return 0;
    }

    return 1;
}

// check single process completion
int isComplete(Process p)
{
    if(p.remain <= 0)
        return 1;
    return 0;
}

// define rr
void rr_fcfs(Process *a, int n)
{
    sort(a,n);

    int i;
    const int N = n;
    int rec[N];

    // settles things for completion check
    for(i = 0; i < n; i++)
    {
        rec[i] = 0;
        a[i].remain = a[i].burst_time;
    }

    printf("Round Robin\n");
    printf("PID  Arrival Time  Burst Time S  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0, quantum = 4;

    //sys_time = a[0].arr_time;
    while(!allCompleted(n,rec))
    {
        for(i = 0; i < n; i++)
        {
            if(sys_time < a[i].arr_time)
                break;

            if(rec[i] == 0 && a[i].arr_time <= sys_time)
            {
                if(a[i].remain == a[i].burst_time)
                {
                    a[i].start = sys_time;
                    a[i].resp_time = a[i].start - a[i].arr_time;
                }

                sys_time += quantum;
                a[i].remain -= quantum;

                if(a[i].remain <= 0)
                {
                    rec[i] = 1;
                    sys_time += a[i].remain;
                    a[i].comp_time = sys_time;
                    a[i].ta_time = a[i].comp_time - a[i].arr_time;
                    a[i].wait_time = a[i].ta_time - a[i].burst_time;

                    resp_sum += a[i].resp_time;
                    ta_sum += a[i].ta_time;
                    wait_sum += a[i].wait_time;
                }
            }
        }        
    }
    
    print(a,n);    
    printf("\nAvg response time: %.2f",(float)resp_sum/n);
    printf("\nAvg turn around time: %.2f",(float)ta_sum/n);
    printf("\nAvg waiting time: %.2f\n",(float)wait_sum/n);
    
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
        a[i].PID = i+1;
        printf("Arrival Time: ");
        scanf("%d",&a[i].arr_time);
        printf("Burst Time: ");
        scanf("%d",&a[i].burst_time);
        //printf("priority: ");
        //scanf("%d",&a[i].priority);
    }

    rr_fcfs(a,n);
}