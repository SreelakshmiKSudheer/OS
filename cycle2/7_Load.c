#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
   pid_t child_pid ;

   child_pid = fork();

   if(child_pid < 0)
   {
      fprintf(stderr,"fork() failed");
      return 1;
   }
   else if(child_pid == 0)
   {
      printf("Child Process says my PID: %d\n",getpid());
      execlp("./Sum.out","Sum",NULL);
      printf("Child process exiting with PID: %d\n",getpid());
      exit(0);
   }
   else
   {
      printf("Parent Process say my PID: %d\n",getpid());
      wait(NULL);
      printf("Parent process says Child process exited\n");
   }
   return 0;
}


