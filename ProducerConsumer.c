#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

int buffer[MAX];                // buffer array
int in = -1, out = -1;
int empty = MAX, full = 0, semaphore = 1,next_produced = 0, next_consumed;

void wait(int *semaphore)
{
    while(*semaphore <= 0);
    (*semaphore)--;
}

void signal(int *semaphore)
{
    (*semaphore)++;
}

void *produce(void *arg)
{
    int i,j;
    for(i = 0; i < 5; i++)
    {
        next_produced++;        // next item is produced in next_produced
        
        wait(&empty);
        wait(&semaphore);
    
        

        signal(&semaphore);
        signal(&full);

        sleep(1);
    }
    pthread_exit(NULL);

}

void *consume()
{
    int i;
    for(i = 0; i < 5; i++)
    {
        wait(&full);
        wait(&semaphore);
        //if(x > 0)
        take();
        printf("Consumer: consumed %d\n",x);
        signal(&semaphore);
        signal(&empty);

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