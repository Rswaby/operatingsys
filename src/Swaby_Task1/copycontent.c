#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc, char *argv[]){

  //this program will mimic the cp linux/unix command using source.txt to destination.txt as
  //as arguments.

   if (argc!=3)
      {
          printf("not enough arguments (i.e ./copy source.txt destination.txt) \n");
          return -1;
      }

  char* sourcePath = argv[1];
  char* destination = argv[2];
  char buffer[1000];
  int returnval;
  int fd;
  int retvalue;
  int fid;

  returnval = access (sourcePath, F_OK);

  if(returnval == -1)
   {
    printf("file %s was not found", argv[1]);
    return 0;
   }
  int ret = open(sourcePath,O_RDONLY);
  /* fd = open(destination, O_RDONLY|O_CREAT); */

  //read file into a buffer
  //write file to destination
  //close source
  //close destination
  if(ret == -1){
    printf("file name %s cannot be open",sourcePath);
    return 0;
  }else{
    fid = read(ret,buffer,1000);
    if(fid == -1){
      printf("file name %s could not be read",sourcePath);
      return 0;
    }else{
      close(ret);
      fd = open(destination, O_CREAT|O_WRONLY,0600);
      retvalue = write(fd,buffer,1000);
      close(fd); 
    }
    
  }
  return 0;     
    

  
  
}
