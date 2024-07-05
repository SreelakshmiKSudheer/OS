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
    int id = *((int*)arg);

    while(1)
    {
        wait_s(&chopstick[id]);
        wait_s(&chopstick[(id+1) % 5]);

        printf("Philosopher %d starts eating\n",id);

        signal_s(&chopstick[id]);
        signal_s(&chopstick[(id+1) % 5]);

        printf("Philosopher %d starts thinking\n",id);

        sleep(1);
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