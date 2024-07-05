#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

int buffer[MAX];                // buffer array
int in = -1, out = -1;
int empty = MAX, full = 0, semaphore = 1;   // semaphores
int next_produced = 0, next_consumed;       // next item to be added or consumed to the shared resource

void wait(int *semaphore)
{
    while(*semaphore <= 0);
    (*semaphore)--;
}

void sig(int *semaphore)
{
    (*semaphore)++;
}

void  pro()
{
    if(in == -1)
        {
            in = 0;
            out = 0;
        }
        else
            in = (in + 1) % MAX;
}

void take()
{
    out = (out+1) % MAX;
    if(out == (in + 1) % MAX)
    {
        in = out = -1;
    }
}

void bufferDisplay()
{
    int j;

    j = out;
    if(out != -1 && in != -1)
    {
        printf("Buffer: [");
        while(j < in)
        {
            printf("%d ",buffer[j]);
            j = (j+1) % MAX;
        }
        printf("%d]\n",buffer[in]);
    }
    else
        printf("Buffer Empty\n");
}

void *produce(void *arg)
{
    int i;
    for(i = 0; i < 5; i++)
    //while(1)
    {
        next_produced++;        // next item is produced in next_produced
        
        wait(&empty);
        wait(&semaphore);       // mutual exculsion to access to the shared resource
    
        pro();
        buffer[in] = next_produced;

        printf("Producer: produced %d\n",buffer[in]);
        bufferDisplay();
        
        sig(&semaphore);
        sig(&full);

        sleep(1);
    }
    pthread_exit(NULL);

}

void *consume()
{
    int i;
    for(i = 0; i < 5; i++)
    //while(1)
    {
        wait(&full);
        wait(&semaphore);
        
        next_consumed = buffer[out];
        printf("Consumer: consumed %d\n",buffer[out]);
        take();
        bufferDisplay();
        
        sig(&semaphore);
        sig(&empty);

        sleep(2);
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