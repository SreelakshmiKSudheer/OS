#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int state[5] = {0,0,0,0,0};
/*
states:
0: thinking
1: hungry
2: eating
*/

int mutex;

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
