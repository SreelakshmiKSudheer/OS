
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        FILE *file;
        char text[20],read[20];
        printf("Enter the content to be written:\n");
        scanf(" %[^\n]",text);
//      printf("%s\n",text);

        file = fopen("Files.txt","w");

        if(file == NULL)
        {
                perror("fopen");
                exit(EXIT_FAILURE);
        }

        if(fwrite(text,sizeof(char),strlen(text),file) != strlen(text))
        {
                perror("fwrite");
                exit(EXIT_FAILURE);
        }

        if(fclose(file) != 0)
        {
                perror("fclose");
                exit(EXIT_FAILURE);
        }

        file = fopen("Files.txt","r");
        if(file == NULL)
        {
                perror("fopen");
                exit(EXIT_FAILURE);
        }

        if(fgets(read,sizeof(read),file) == NULL)
        {
                perror("fgets");
                exit(EXIT_FAILURE);
        }

        if(fclose(file) != 0)
        {
                perror("fclose");
                exit(EXIT_FAILURE);
        }

        printf("Content read frome file:\n%s\n",read);

        return 0;

}



