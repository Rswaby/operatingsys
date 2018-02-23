#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]){

  //this program will mimic the cp linux/unix command using source.txt to destination.txt as
  
  //as arguments.
  if( argc  < 2){
    printf("Does not have enough arguments: we need a source.txt and destination.txt");
    return 1;
  }

  char* sourcePath = argv[1];
  char* destination = argv[2];
  char buffer[100];
  char buffer2[100];
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
  retvalue = open(sourcePath,O_RDONLY);
  
  fd = open(destination,O_CREAT|O_WRONLY,0666);

  if(retvalue < 0){
    printf("File name %s could not open", sourcePath);
    perror("Open");
    return 1;
  }
  if(fd < 0){
    printf("File name %s could not open", destination);
    perror("Open");
    return 1;
  }



  while(1)
    {
      int i;

       fid = read(retvalue,buffer,100);
       if(fid < 100){
	 buffer[fid] = '\0';
	 for(i = 0; i<100; i++)
	   {

	     if(buffer[i] == '1')
	       buffer[i]='a';
	     else
	       buffer2[i] = buffer[i];
	   }
	 break;
       }else{
	 for(i = 0; i < 100; i++)
	   {
	     if(buffer[i] == '1')
	       buffer[i]='a';
	     else
	       buffer2[i] = buffer[i];
	   }
       }
       //writing to destination file

       write(fd,buffer,100);
       write(fd,"XYZ",3);
       printf("%s \n",buffer);
    }
  close(retvalue);
  close(fd);

  return 0;

}

  
    
    
     
