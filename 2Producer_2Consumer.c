#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

int buffer[MAX];
int empty = MAX, full = 0, pmutex = 1, pc_mutex = 1, cmutex = 1;
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
        out = 0;
    in = (in+1) % MAX;
}

void outUpdate()
{
    out = (out + 1) % MAX;
    if(out == (in+1) % MAX)
        out = in = -1;
}

void *produce(void *arg)
{
    int id = *((int*)arg);
    int item;
    if(id == 1)
        item = 1;
    else
        item = 2;

    while(1)
    {
        wait_s(&pmutex);
        wait_s(&empty);
        wait_s(&pc_mutex);
        

        inUpdate();
        buffer[in] = item;
        printf("Producer %d: produced item %d\n", id,buffer[in]);
        bufferDisplay();
        //sleep(1);
        item += 2;
        
        signal_s(&pc_mutex);
        signal_s(&full);
        signal_s(&pmutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consume(void *arg)
{
    int id = *((int*)arg);

    while(1)
    {
        wait_s(&cmutex);
        wait_s(&full);
        wait_s(&pc_mutex);

        printf("Consumer %d: consumes %d\n",id,buffer[out]);
        outUpdate();
        bufferDisplay();
        
        signal_s(&pc_mutex);
        signal_s(&empty);
        signal_s(&cmutex);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main()
{
    int pid[2],cid[2],i;
    pthread_t producer[2],consumer[2];

    for(i = 0; i < 2; i++)
    {
        pid[i] = i+1;
        pthread_create(&producer[i],NULL,produce,&pid[i]);
    }

    for(i = 0; i < 2; i++)
    {
        cid[i] = i+1;
        pthread_create(&consumer[i],NULL,consume,&cid[i]);
    }

    for(i = 0; i < 2; i++)
    {
        pthread_join(producer[i],NULL);
    }

    for(i = 0; i < 2; i++)
    {
        pthread_join(consumer[i],NULL);
    }
}