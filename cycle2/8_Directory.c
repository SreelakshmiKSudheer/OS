
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
        DIR *dir;
        struct dirent *entry;
        struct stat file_stat;

        dir = opendir(".");

        if(dir == NULL)
        {
                perror("opendir");
                exit(EXIT_FAILURE);
        }

        while((entry = readdir(dir)) != NULL)
        {
                if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
                        continue;
                if(stat(entry->d_name,&file_stat) == -1)
                {
                        perror("stat");
                        exit(EXIT_FAILURE);
                }

                printf("File name = %s\n",entry->d_name);
                printf("File size = %ld bytes\n",file_stat.st_size);
                printf("File mode = %o \n",file_stat.st_mode);
                printf("Owner UID = %d \n",file_stat.st_uid);
                printf("Group GID = %d \n",file_stat.st_gid);
                printf("Last accessed time = %ld\n",file_stat.st_atime);
                printf("Last modified time = %ld\n\n",file_stat.st_mtime);
        }
        return 0;
}




