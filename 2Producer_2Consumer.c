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

void inUpdate()
{
    if(in == -1)
    {
        in = out = 0;
    }
    else
        in = (in+1) % MAX;
}

void outUpdate()
{
    out = (out+1) % MAX;
    if(out == (in+1) % MAX)
        in = out = -1;
}

void *produce(void *arg)
{
    int id = *((int*)arg);
    while(1)
    {
        

        wait_s(&empty);
        wait_s(&semaphore);
        
        next_produced++;
        inUpdate();
        buffer[in] = next_produced;
        printf("Producer %d: Produced item %d\n",id,buffer[in]);
        bufferDisplay();
        
        signal_s(&semaphore);
        signal_s(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consume(void *arg)
{
    int id = *((int*)arg);

    while(1)
    {
        wait_s(&full);
        wait_s(&semaphore);
        
        next_consumed = buffer[out];
        printf("Consumer %d: consumed item %d\n",id,buffer[out]);
        outUpdate();
        bufferDisplay();

        signal_s(&semaphore);
        signal_s(&empty);

        sleep(3);
    }
    pthread_exit(NULL);
}

int main()
{
    int pid[2], cid[2],i;
    pthread_t pro[2], con[2];

    for(i = 0; i < 2; i++)
    {
        pid[i] = i+1;
        pthread_create(&pro[i],NULL,produce,&pid[i]);
    }
    for(i = 0; i < 2; i++)
    {
        cid[i] = i+1;
        pthread_create(&con[i],NULL,consume,&cid[i]);
    }
    for(i = 0; i < 2; i++)
    {
        pthread_join(pro[i],NULL);
    }
    for(i = 0; i < 2; i++)
    {
        pthread_join(con[i],NULL);
    }
    return 0;
}