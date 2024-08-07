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

void print(Process *a, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%2d%15d%12d%15d%17d%18d%14d\n",a[i].PID,a[i].arr_time,a[i].burst_time,a[i].resp_time,a[i].comp_time,a[i].ta_time,a[i].wait_time);

    }
}
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

void sjf(Process *a, int n)
{
    sort(a,n);

    int i,j,min;
    const int N = n;
    int rec[N];

    for(i = 0; i < n; i++)
        rec[i] = 0;

    printf("Shortest Job First\n");
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0;

    for(i = 0; i < n; i++)
    {

            if(allCompleted(n,rec))
                break;
            else
            {
                
                for(j = 0; j < n; j++)
                {
                    if(rec[j] == 0)
                    {
                        min = j;
                        break;
                    }
                }
            
                
                for(j = 0; j < n; j++)
                {
                    if(a[j].arr_time <= sys_time && rec[j] == 0)
                    {
                        if(a[j].burst_time < a[min].burst_time)
                            min = j;
                    }
                    //printf("min = %d\n",min);
                }
                
                if(sys_time < a[min].arr_time)
                {
                    sys_time = a[min].arr_time;
                }

                a[min].start = sys_time;
                a[min].resp_time = a[min].start - a[min].arr_time;
                a[min].comp_time = a[min].start + a[min].burst_time;
                a[min].ta_time = a[min].comp_time - a[min].arr_time;
                a[min].wait_time = a[min].ta_time - a[min].burst_time;

                sys_time = a[min].comp_time;
                rec[min] = 1;

                resp_sum += a[min].resp_time;
                ta_sum += a[min].ta_time;
                wait_sum += a[min].wait_time;

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

    sjf(a,n);
}