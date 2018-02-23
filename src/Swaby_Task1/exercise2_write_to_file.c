#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int fd;
  if(argc =! 2)
    {
      printf("\n Usage \n");
      return 1;
    }

  errno = 0;
  fd = open(argv[1], O_RDONLY|O_CREAT);
  
  if(fd == -1)
    {
      printf("\n open() failed with error [%s]\n",strerror(errno));
      return 1;
    }

  else
    {
      printf("\n Create and Open() Succesful \n");

      return 0;
    }
      
}
