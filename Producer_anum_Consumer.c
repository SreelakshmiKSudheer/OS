#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 5

char buffer[MAX];
int empty = MAX, full = 0, pmutex = 1, pc_mutex = 1;
int in = -1, out = -1;

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
            printf("%c ",buffer[i]);
            i = (i+1) % MAX;
        }
        printf("%c]\n",buffer[in]);
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
    char id = *((char*)arg);
    char item;
    if(id == '1')
        item = '1';
    else
        item = 'a';

    while(1)
    {
        wait_s(&pmutex);
        wait_s(&empty);
        wait_s(&pc_mutex);
        
        //wait_s(&empty);

        inUpdate();
        buffer[in] = item;
        printf("Producer %c: produced item %c\n", id,buffer[in]);
        bufferDisplay();
        //sleep(1);
        
        if(id == '1')
        {
            if(item == '9')
                item = '1';
            else
                item += 1;
        }
        if(id == 'a')
        {
            if(item == 'z')
                item = 'a';
            else
                item += 1;
        }
        
        //signal_s(&full);
        
        signal_s(&pc_mutex);
        signal_s(&full);
        signal_s(&pmutex);
        sleep(2);
    }
    pthread_exit(NULL);
}

void *consume(void *arg)
{

    while(1)
    {
        wait_s(&full);
        wait_s(&pc_mutex);

        printf("Consumer : consumes %c\n",buffer[out]);
        outUpdate();
        bufferDisplay();
        
        signal_s(&pc_mutex);
        signal_s(&empty);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main()
{
    char num = '1', ch = 'a';
    pthread_t producerNum,producerAlpha,consumer;

    pthread_create(&producerNum,NULL,produce,&num);
    pthread_create(&producerAlpha,NULL,produce,&ch);
    pthread_create(&consumer,NULL,consume,NULL);

    pthread_join(producerNum,NULL);
    pthread_join(producerAlpha,NULL);
    pthread_join(consumer,NULL);

}