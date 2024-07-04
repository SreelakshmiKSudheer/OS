#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *mutex;        //  ensure mutual exclusion when the variable read_count is updated
int *rw_mutex;     // mutual exclusion of reader and writer semaphores
int read_count;    // keeps track of the no. of readers
int shr = 0;       // shared resource

void wait_s(int *semaphore)
{
    while(*semaphore <= 0);
    // do nothing
    *semaphore--;
}

void signal_s(int *semaphore)
{
    *semaphore++;
}

void writer(void *arg)
{
    int writer_id = *((int*)arg);       // writer_id given as the function parameter

    while(1)
    {
        wait_s(&rw_mutex);

        shr++;
        printf("Writer %d: Wrote data %d",writer_id,shr);

        signal_s(&rw_mutex);
    }
}