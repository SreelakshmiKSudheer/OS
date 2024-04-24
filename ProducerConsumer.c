#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 5

int E = MAX, F = 0, S = 1,x = 0;

void wait(int *semaphore)
{
    while(*semaphore <= 0);
    (*semaphore)--;
}

void sig(int *semaphore)
{
    (*semaphore)++;
}

void pro()
{
    if(x < MAX)
        x++;
}
void take()
{
    if(x > 1)
        x--;
}
void *produce()
{
    while(1)
    {
        wait(&E);
        wait(&S);
        //if(x < MAX)
        pro();
        printf("Producer: produced %d\n",x);
        sig(&S);
        sig(&F);
    }
    pthread_exit(NULL);

}

void *consume()
{
    while(1)
    {
        wait(&F);
        wait(&S);
        //if(x > 0)
        take();
        printf("Consumer: consumed %d\n",x);
        sig(&S);
        sig(&E);
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t producer,consumer;

    pthread_create(&producer,NULL,produce,NULL);
    pthread_create(&consumer,NULL,consume,NULL);

    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
}