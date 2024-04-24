#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct resource
{
        char msg[100];
        int chance,exit,src;
}resource;

int main()
{
        resource *ptr;
        char *name = "sharememory";
        int id = shm_open(name,O_CREAT | O_RDWR,0666);
        ftruncate(id,sizeof(resource));
        ptr = mmap(0,sizeof(resource), PROT_WRITE| PROT_READ, MAP_SHARED,id,0);

        while(!ptr->exit)
        {       
                if(ptr->chance == 3)
                {
                        printf("Enter message: ");
                        scanf(" %[^\n]", ptr->msg);
                        if(!strcmp(ptr->msg,"exit"))
                                ptr->exit = 1;
                        ptr->chance = 2;
                }
                else if(ptr->chance == 4)
                {
                        printf("Message from server: %s\n",ptr->msg);
                        ptr->chance = 3;
                }
        }
        munmap(ptr,sizeof(resource));
        return 0;
}



                                           
                                          
