#include <sys/wait.h>             /* Needed to use wait() */
#include <stdio.h>                  
#include <stdlib.h>
#include <unistd.h>               /* UNIX and POSIX constants and functions (fork, pipe) */
#include <string.h>               /* Needed to use strlen() */
#include <errno.h>
#include <signal.h> 

int main(int argc, char *argv)

{
	void sigint_handler(int sig);
    printf("Program finished");

	 if (signal(SIGINT, sigint_handler) == SIG_ERR){
 perror("signal");
 exit(1);
}
{
	 char answer;
printf("Are you my parent? > "); scanf("%s", &answer);
printf("You are %s my parent", answer); 
 
 int pipefd[2];
 pid_t cpid;
 char buf;
 if (argc != 2) 
  {
   fprintf(stderr, "Usage: %s \n", argv[0]);
   exit(EXIT_FAILURE);
  }
 if (pipe(pipefd) == -1)          /* An error has occurred. */
  {
   fprintf(stderr, "%s", " Call to pipe() has failed.\n");           
   exit(EXIT_FAILURE);
  }
 cpid = fork();                   /* fork() returns the child process's PID  */
 if (cpid == -1)                 
  {
   fprintf(stderr, "%s", " Call to fork() has failed.\n");
   exit(EXIT_FAILURE);
  }
 if (cpid == 0) 
  {                               /* Child reads from pipe */
   printf("I am the child.\n");
   close(pipefd[1]);              /* Close unused write end */

  } 
 else 
  {                               /* Parent writes argv[1] to pipe */
   printf("I am the parent.\n", answer);
   close(pipefd[0]);              /* Close unused read end */
   write(pipefd[1], argv[1], strlen(argv[1]));
   close(pipefd[1]);             
   wait(NULL);                    
   exit(EXIT_SUCCESS);
  }
  return 0;
}
}
