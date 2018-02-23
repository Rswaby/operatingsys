#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
  int fd;
  if(argc =! 2)
    {
      printf("\n Usage \n");
      return 1;
    }

  int openreturn;
  int readreturn;
  int writereturn;
  int bts;
  char buff[1000];

  errno = 0;
  openreturn = open(argv[1], O_RDONLY);

  if(openreturn == -1)
    {
      printf("\n failed to open file with arror [%s]",strerror(errno));
      perror("Open");
      return 1;
    }

    readreturn = read(openreturn, buff ,1000);

    if(readreturn == -1)
      {
	printf("\n failed to read file with arror [%s]",strerror(errno));
	perror("Read");
      }
    
    else
      printf("%s\n",buff);
  
  
  close(openreturn);
  return 0;
}
