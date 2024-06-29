#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

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
    x++;
}
void take()
{
    if(x > 0)
        x--;
}
void *produce(void *arg)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        wait(&E);
        wait(&S);
        //if(x < MAX)
        pro();
        printf("Producer: produced %d\n",x);
        sig(&S);
        sig(&F);

        sleep(1);
    }
    pthread_exit(NULL);

}

void *consume()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        wait(&F);
        wait(&S);
        //if(x > 0)
        take();
        printf("Consumer: consumed %d\n",x);
        sig(&S);
        sig(&E);

        sleep(1);
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