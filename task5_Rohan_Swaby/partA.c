#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>


#define SIZE 10
int _index = 0 ,y = 0;//shared data

int *buffer;//shared data

void *consumer(void *param/* arguments */);//the thread
//void *producer(void *param/* arguments */);
int main(int argc, char const *argv[]) {
  pthread_t cons;
  pthread_attr_t attr;
  /* code */
  //initialze array
  pthread_attr_init(&attr);
  buffer = (int *) malloc(sizeof(int) * SIZE);
  for (size_t i = 0; i < SIZE; i++) buffer[i] = 0;

  int thre = pthread_create(&cons,&attr,consumer,NULL);
  if(thre != 0)
  {
    printf("Unable to create thread \n" );
  }
  //=====================producer====================
  while (1) {
    if (_index < SIZE) {
      printf("Producer %d\n",_index );
      buffer[_index] = 1;
      _index++;
    }
  }
  //=================================================
  if (buffer) {
    /* code */
    free(buffer);
  }
  pthread_exit(NULL);
}

void *consumer(void *param/* arguments */) {
  /* code */
  while (1) {
    /* code */
    if (_index > 0) {
      printf("consumer %d\n", _index);
      _index--;
      buffer[_index] = 99;
    }


  }
  //printf("this is consumer\n");
}
