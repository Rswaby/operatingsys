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

int main(int argc, char const *argv[]) {
  //we'll have to create paramList for Prcs_P1 and Prcs_P2
  char *const paramListP1[] = {"Prcs_P1",NULL};
  char *const paramListP2[] = {"Prcs_P2",NULL};

  int child = fork();

  if(child == 0)
  {
    printf("Child 1 PID: %d\n", getpid());
    printf("Executing ./Prcs_P2 \n");
    execv("./Prcs_P1",paramListP1);


  }else{
    int status;

    waitpid(child, &status,0);

    int child1 = fork();
    if (child1 == 0) {
      /* code */
      printf("child2 with pid: %d\n",getpid());
      printf("Executing ./Prcs_P2 \n");
      execv("./Prcs_P2",paramListP2);

    }
    else
    {
      int status;
      int pid = waitpid(child1,&status,0);
      printf("waiting for child2 with : %d\n", pid);

    }
  }

  return 0;
}
