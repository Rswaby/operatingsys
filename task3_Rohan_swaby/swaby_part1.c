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

  //Fork a new child process
  child = fork();
  if(child == 0){
    //here we are going to use execl
    printf("Child PID: %d \n",getpid());
    execl("/bin/date","date",NULL);
    //the following line will print if execl fails
    perror("execl() failed");
    
  }else{
    printf("Parent \n");
    wpid = waitpid(child, &status, 0);
    printf("End of parent \n");
  }
  return 0; 
}
