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

int main(int argc, char* argv[])
{
  int dest1;
  int dest2;
  int checkdes1;
  int checkdes2;

  //check if the files are already created

  checkdes1 = access("destination1.txt",F_OK);
  checkdes2 = access("destination2.txt",F_OK);

  if(checkdes1 != 0){
    dest1 = open("destination1.txt", O_RDWR | O_CREAT,0600);
    printf("destination1.txt was created \n");
    close(dest1);
  }
  else{
    printf("a destination1.txt was found  \n");
   }

  if(checkdes2 != 0){
    dest2 = open("destination2.txt",O_RDWR | O_CREAT,0600);
    printf("destination2.txt was created \n");
    close(dest2);
  }else{
    printf("there is already an destination2.txt \n");  
  }

  return 0;
  }
