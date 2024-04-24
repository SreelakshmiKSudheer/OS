#include <stdio.h>
#include <pthread.h>

int turn, flag[2];

void lock(int self)
{
    flag[self] = 1;
    turn = 1 - self;

    while(flag[1 - self] && turn == 1 - self);
}

void unlock(int self)
{
    flag[self] = 0;
}

void* process(void* arg)
{
    int self = *(int*)arg;

    printf("T%d entering crit\n",self);
    lock(self);
    
    printf("T%d exiting crit\n",self);
    unlock(self);

    printf("T%d exited crit\n",self);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1,t2;
    int even = 2,odd = 1;

    flag[0] = 0;
    flag[1] = 0;
    turn = 0;

    pthread_create(&t1,NULL,process,&odd);
    pthread_create(&t2,NULL,process,&even);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}