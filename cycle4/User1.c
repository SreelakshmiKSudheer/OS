#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct area
{
    int server_up;
    int client_up;
    int rw;
    char msg[100];
};

struct area *shmptr;

int main()
{
    int shmid;
    shmid = shmget(700, sizeof(struct area), IPC_CREAT | 0666);
    shmptr = (struct area *)shmat(shmid, NULL, 0);
    shmptr->rw = 0; 

    while (1)
    {
        
        while (shmptr->rw != 1)
            ;
     while(shmptr->client_up == 0)
        {
            printf("get from user 2:");
            if(strcmp(shmptr->msg, "stop") == 0)
            {
                
                exit(1);
            }
            else
            {
                puts(shmptr->msg);
            }
            shmptr->server_up = 0;
            shmptr->client_up = 1;
        }
        
        printf("user1:");
        if(strcmp(shmptr->msg, "stop") == 0) 
        {
            exit(1);
        }
        else
        {
            fgets(shmptr->msg, 100, stdin);
            shmptr->msg[strcspn(shmptr->msg, "\n")] = '\0'; 
        }
        
        shmptr->rw = 0;
    }
    
    shmctl(shmid, IPC_RMID, NULL);
    return  0;
}