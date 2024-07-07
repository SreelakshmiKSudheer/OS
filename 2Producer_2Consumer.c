#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

int buffer[MAX];
int empty = MAX, full = 0, semaphore = 1;
int in = -1, out = -1;
int next_produced = 0, next_consumed;

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

void bufferDisplay()
{
    if(out != -1 && in != -1)
    {
        int i = out;
        printf("Buffer: [");
        while(i != in)
        {
            printf("%d ",buffer[i]);
            i = (i+1) % MAX;
        }
        printf("%d]\n",buffer[in]);
    }
    else
        printf("Buffer empty\n");
}

