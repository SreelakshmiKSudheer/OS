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
    int i,j;                    // loop variables
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

// check single process completion
int isComplete(Process p)
{
    if(p.remain <= 0)
        return 1;
    return 0;
}

// check completion of all process at once
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

// define fcfs
void fcfs(Process *a, int n)
{
    sort(a,n);

    int i;
    printf("First Come First Serve\n");
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0;

    for(i = 0; i < n; i++)
    {

        if(sys_time < a[i].arr_time)
        {
            sys_time = a[i].arr_time;
        }

        // sets
        a[i].start = sys_time;
        a[i].resp_time = a[i].start - a[i].arr_time;
        a[i].comp_time = a[i].start + a[i].burst_time;
        a[i].ta_time = a[i].comp_time - a[i].arr_time;
        a[i].wait_time = a[i].ta_time - a[i].burst_time;

        sys_time = a[i].comp_time;

        resp_sum += a[i].resp_time;
        ta_sum += a[i].ta_time;
        wait_sum += a[i].wait_time;

    }

    print(a,n);
    printf("\nAvg response time: %.2f",(float)resp_sum/n);
    printf("\nAvg turn around time: %.2f",(float)ta_sum/n);
    printf("\nAvg waiting time: %.2f\n",(float)wait_sum/n);
    
}

// define sjf
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
                    if(a[j].arr_time <= sys_time)
                    {
                        if(a[j].burst_time < a[min].burst_time && rec[j] == 0)
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
    printf("\nAvg waiting time: %.2f\n",(float)wait_sum/n);
    
}

// define ps
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

            if(allCompleted(n,rec))
                break;
            else
            {
                // checks for process with most priority
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
    printf("\nAvg waiting time: %.2f\n",(float)wait_sum/n);
    
}

// define rr
void rr(Process *a, int n)
{
    sort(a,n);

    int i,j,prior;
    const int N = n;
    int rec[N];

    // settles things for completion check
    for(i = 0; i < n; i++)
    {
        rec[i] = 0;
        a[i].remain = a[i].burst_time;
    }

    printf("Round Robin\n");
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0, quantum = 4;

    for(i = 0; i < n; i++)
    {

            if(allCompleted(n,rec))
                break;
            else
            {
                
                while(!allCompleted(n,rec))
                {
                    // finding process with highest priority
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
                        sys_time += quantum;
                        continue;
                    }
                    
                    if(sys_time < a[prior].arr_time)
                    {
                        sys_time = a[prior].arr_time;
                    }
                    
                    // setting starting time and response time of the process
                    if(a[prior].remain == a[prior].burst_time)
                    {
                        a[prior].start = sys_time;
                        a[prior].resp_time = a[prior].start - a[prior].arr_time;
                    }
                    
                    // update system time
                    sys_time += quantum;

                    // update remaining time of each process
                    a[prior].remain -= quantum;
                    
                    // check whether the current process is complete or not
                    if(isComplete(a[prior]))
                    {
                        sys_time += a[prior].remain;
                        a[prior].comp_time = sys_time;                                      // set completion time
                        a[prior].ta_time = a[prior].comp_time - a[prior].arr_time;          // set turn around time
                        a[prior].wait_time = a[prior].ta_time - a[prior].burst_time;        // set waiting time

                        rec[prior] = 1;                                                     // process completion recorded

                        resp_sum += a[prior].resp_time;                                     // summing response times for avg
                        ta_sum += a[prior].ta_time;                                         // summing turn around times for avg
                        wait_sum += a[prior].wait_time;                                     // summing waiting times for avg
                    }

                }

        }
    }

    // prints 
    print(a,n);

    printf("\nAvg response time: %.2f",(float)resp_sum/n);
    printf("\nAvg turn around time: %.2f",(float)ta_sum/n);
    printf("\nAvg waiting time: %.2f\n",(float)wait_sum/n);
    
}

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
    printf("PID  Arrival Time  Burst Time  Response Time  Completion Time  Turn Around Time  Waiting Time\n");

    int sys_time = 0, resp_sum = 0, ta_sum = 0,wait_sum = 0, quantum = 4;

    //sys_time = a[0].arr_time;
    while(!allCompleted(n,rec))
    {
        for(i = 0; i < n; i++)
        {
            if(sys_time < a[i].arr_time)
                sys_time = a[i].arr_time;

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
        printf("Process ID: ");
        scanf("%d",&a[i].PID);
        printf("Arrival Time: ");
        scanf("%d",&a[i].arr_time);
        printf("Burst Time: ");
        scanf("%d",&a[i].burst_time);
        printf("Priority: ");
        scanf("%d",&a[i].priority);
    }

// call the different CPU scheduling functions
    fcfs(a,n);
    sjf(a,n);
    ps(a,n);
    rr(a,n);
    rr_fcfs(a,n);


}