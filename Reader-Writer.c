#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *mutex;        //  ensure mutual exclusion when the variable read_count is updated
int *rw_mutex;     // mutual exclusion of reader and writer semaphores
int read_count;    // keeps track of the no. of readers
int shr = 0;       // shared resource

void s_wait(int *semaphore)
{
    while(*semaphore <= 0);
    // do nothing
    *semaphore--;
}

void s_signal(int *semaphore)
{
    *semaphore++;
}

