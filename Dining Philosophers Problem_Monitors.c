#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int state[5] = {1,1,1,1,1};
int self[5];
/*
states:
1: thinking
2: hungry
3: eating
*/

int mutex = 0;

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

void test(int i)
{
    if(state[(i+1) % 5] != 3 && state[i] == 2 && state[(i+4) % 5] != 3)
    {
        state[i] = 3;
        printf("Philosopher %d is eating\n",i);
        self[i] = 0;
    }
}

void pickup(int i)
{
    wait_s(&mutex);
    state[i] = 2;
    printf("Philosopher %d is hungry\n",i);
    test(i);
    signal_s(&mutex);
    if(state[i] != 3)
        self[i] = 1;                                            // waiting
}

void drop(int i)
{
    //wait_s(&mutex);
    state[i] = 1;
    test((i+1) % 5);
    test((i+4) % 5);

    //signal_s(&mutex);
}

void *philosopher(void *arg)
{
    int id = *((int*)arg);
    while(1)
    {
        sleep(1);
        pickup(id);
        sleep(0);
        drop(id);
    }
    pthread_exit(NULL);
}

int main()
{
    int i, id[5];
    pthread_t ph[5];

    for(i = 0; i < 5; i++)
    {
        id[i] = i+1;
        pthread_create(&ph[i],NULL,philosopher,&id[i]);
    }

    for(i = 0; i < 5; i++)
    {
        pthread_join(ph[i],NULL);
    }

    return 0;
}