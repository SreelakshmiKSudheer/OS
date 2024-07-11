#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct
{
	char msg[100];
	int chance, exit;

}resource;

int main()
{
	const int SIZE = sizeof(resource);
	const  char *name = "client_server";

	int shm_fd;
	resource *ptr;

	shm_fd = shm_open(name,O_RDWR,0666);
	ftruncate(shm_fd,SIZE);
	ptr = mmap(0,SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);

	while(!ptr->exit)
	{
		if(ptr->chance == 3)
		{
			printf("Enter message: ");
			scanf(" %[^\n]",ptr->msg);
			ptr->chance = 2;
		}
		else if(ptr->chance == 4)
		{
			printf("Message from client: %s\n",ptr->msg);
			ptr->chance = 3;
		}
		sleep(1);

	}

	munmap(ptr,SIZE);
	sleep(1);
}
