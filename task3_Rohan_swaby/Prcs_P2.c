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

char * swap(char arr[],size_t count ,char target,char replace_with);
int checkbytes(int count, int i,int target);

int main(int argc, char* argv[])
{
  int source;
  int destination1;
  int destination2;

  char buffer100[100];
  char buffer50[50];

  int returnSource;
  int returnDestination1;
  int returnDestination2;

  returnSource = access("source.txt",F_OK);
  if (returnSource == -1) {
    /* code */
    printf("Source.txt does not exist \n");
    return -1;
  }

  source = open("source.txt",O_RDWR);
  if (source == -1) {
    /* code */
    perror("Open() failed source.txt");
    return -1;
  }
  //=====================================================
  destination1 = open("destination1.txt",O_WRONLY);
  destination2 = open("destination2.txt",O_WRONLY);
  if (destination1 == -1) {
    /* code */
    perror("Open() failed on destination1.txt");
    return -1;
  }

  if (destination2 == -1) {
    /* code */
    perror("Open() failed on destination2.txt");
    return -1;
  }


  int pid;
  size_t count = 1292;
  int bytes;
  int write1;

  for (size_t i = 0; i < count; i=i+150) {
    /* code */
    pid = read(source,buffer100,100);
    //char * buf100;
    //char * buf50;

    //buffer100 = swap(buffer100, count ,'A','1');

    for(int j =0; j< 100; j++)
		{
			if(buffer100[j] == '1')
			{
				buffer100[j] = 'A';
			}
		}

     //do swapping Here
    bytes = checkbytes(count,i,100);
    write1 = write(destination1,buffer100,bytes);
    //check
    if (bytes < 100) {
      /* code */
      break;
    }
    /// may need to use lseek;
    int bytes50 = 50;
    pid = read(source,buffer50,50);
    //buffer50 = swap(buffer50,50,'B','2');s
    for(int j =0; j< 50; j++)
		{
			if(buffer50[j] == '2')
			{
				buffer50[j] = 'B';
      }
		}

    bytes50 = checkbytes(count,i,50);
    int write2 = write(destination2,buffer50,bytes50);

  }
  close(source);
  close(destination1);
  close(destination2);

  return 0;

}

int checkbytes(int count, int i,int target){
  int bytes;
  if(count - i > target) //THis statement controlls whether or not we will need to handle the case when there is less than 100 chars
  {
    bytes = target;

  }
  else
  {
    bytes = count - i;
  }

  return bytes;
}

char * swap(char arr[],size_t count ,char target,char replace_with){
  size_t i = 0;
  for (i = 0; i < count; i++) {
    /* code */
    if (arr[i] == target) {
      /* code */
      arr[i] = replace_with;
    }
  }
  return arr;
}
