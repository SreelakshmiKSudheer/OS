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
        printf("%2d%15d%12d%15d%17d%18d%14d\n",a[i].PID,a[i].arr_time,a[i].burst_time,a[i].resp_time,a[i].comp_time,a[i].ta_time,a[i].wait_time);

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

// define priority scheduling
void ps(Process *a, int n)
{
    sort(a,n);

    int i,j,prior;
    const int N = n;
    int rec[N];

    for(i = 0; i < n; i++)
        rec[i] = 0;

    printf("Priority scheduling\n");
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0;

    for(i = 0; i < n; i++)
    {
            // check whether all processes are completed or not
            if(allCompleted(n,rec))
                break;
            else
            {
                // checks for incomplete process with most priority
                prior = -1;
                for (j = 0; j < n; j++) 
                {
                    if (rec[j] == 0 && a[j].arr_time <= sys_time) 
                    {
                        if (prior == -1 || a[j].priority < a[prior].priority)
                            prior = j;
                    }
                }

                if (prior == -1) 
                {
                    sys_time++;
                    continue;
                }
                
                if(sys_time < a[prior].arr_time)
                {
                    sys_time = a[prior].arr_time;
                }

                // sets
                a[prior].start = sys_time;
                a[prior].resp_time = a[prior].start - a[prior].arr_time;
                a[prior].comp_time = a[prior].start + a[prior].burst_time;
                a[prior].ta_time = a[prior].comp_time - a[prior].arr_time;
                a[prior].wait_time = a[prior].ta_time - a[prior].burst_time;

                sys_time = a[prior].comp_time;
                rec[prior] = 1;

                resp_sum += a[prior].resp_time;
                ta_sum += a[prior].ta_time;
                wait_sum += a[prior].wait_time;

        }
    }

    print(a,n);

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
        printf("Priority: ");
        scanf("%d",&a[i].priority);
    }

    ps(a,n);
}