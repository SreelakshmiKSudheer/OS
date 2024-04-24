#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int semaphore = 1;
int state = 1;

void wait(int *semaphore)
{
        while(*semaphore <= 0)
        {
                *semaphore--;
        }
}

void signal(int *semaphore)
{
        sleep(1);
        *semaphore++;
}

void *thread_f(void *arg)
{
        int n = *((int *)arg);
        int st = n;

        while(1)
        {
                wait(&semaphore);
                if(state == st)
                {
                        printf("From thread(%d) - %d\n",st,n);
                        n += 2;
                        state = 3 - st;
                }
                signal(&semaphore);
        }
        pthread_exit(NULL);
}


int main()
{
        pthread_t tid1, tid2;
        int odd = 1, even = 2;

        pthread_create(&tid1, NULL,(void *)thread_f,&odd);
        pthread_create(&tid2, NULL,(void *)thread_f,&even);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);

}
