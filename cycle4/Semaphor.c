#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int semaphore = 1;
int turn = 1;

void wait(int *semaphore)
{
        while(*semaphore <= 0)
        {
                (*semaphore)--;
        }
}

void sig(int *semaphore)
{
        sleep(1);
        (*semaphore)++;
}

void *thread_f(void *arg)
{
        int n = *((int *)arg);
        int id = n;

        while(1)
        {
                wait(&semaphore);
                if(turn == id)
                {
                        printf("From thread(%d) - %d\n",id,n);
                        n += 2;
                        turn = 3 - id;
                }
                sig(&semaphore);
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
