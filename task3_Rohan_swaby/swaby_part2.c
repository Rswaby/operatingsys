
//Author: Rohan Swaby
//course: Operating system
//instructor: Peter Barnett

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
  int child;
  int status;
  int wpid;

  char *const parmList[] = {"ls","-l","--color","-a","/usr/bin", NULL};

  //Fork a new child process#include <>
  child = fork();
  if(child == 0){
    //this we are in the child process execp
    printf("Child Fork successful with PID: %d \n",getpid());
    execvp("ls", parmList);
    perror("execvp() failed");//this line will execute if failed

  }else{
    printf("this is the parent \n");
    int pid = waitpid(child,&status,0);
    //end of the file
  }

  return 0;
 
}
