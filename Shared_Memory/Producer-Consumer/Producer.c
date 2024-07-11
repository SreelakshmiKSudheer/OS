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
	const char *name = "Producer_Consumer";

	int shm_fd;
	resource *ptr;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
	ptr = mmap(0,SIZE,PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd,0);

	ptr->chance = 1;
	ptr->exit = 0;

	while(!ptr->exit)
	{
		if(ptr->chance == 1)
		{
			printf("Produce: ");
			scanf(" %[^\n]",ptr->msg);
			if(!strcmp(ptr->msg,"exit"))
				ptr->exit = 1;
			ptr->chance = 2;
		}
		sleep(1);
	}

	printf("exited - %d\n",ptr->exit);
	sleep(1);
	munmap(ptr,SIZE);
	shm_unlink(name);
}

