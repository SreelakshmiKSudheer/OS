#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int chopstick[5] = {1,1,1,1,1};

void wait_s(int *semaphore)
{
    while(*semaphore <= 0);
    // do nothing
    (*semaphore)--;
}

void signal_s(int *semaphore)
{
    (*semaphore)++;
}

void *philosopher(void *arg)
{
    
}