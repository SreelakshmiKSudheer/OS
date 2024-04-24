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
      printf("Child Process: PID: %d, PPID: %d\n",getpid(),getppid());
      exit(0);
   }
   else
   {
      printf("Parent Process: PID: %d, PPID: %d\n",getpid(),getppid());
      wait(NULL);
      printf("Child process exited\n");
   }
   return 0;
}


