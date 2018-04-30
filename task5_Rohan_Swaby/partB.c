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


#define SHMOBJ_PATH  "/spam"
//#define MEM_SIZE 4096

#define MEM_SIZE 10
int _index = 0 ,y = 0;//shared data
void *buffer;//shared data

void *producer(void *S_PATH);
void *consumer(void *S_PATH);
//const char* string1 = "produce"
//const char* string2 = "consume"
int  main(int argc, char const *argv[]) {
  pthread_t thread1,thread2;
  void *status;
  //create pthread for producer
  int t1 = pthread_create(&thread1,NULL,producer,SHMOBJ_PATH);
  if(t1!=0)
  {
    printf("Thread1 could not be created \n");
    return -1;
  }
  int t2 = pthread_create(&thread1,NULL,consumer,SHMOBJ_PATH);
  if (t2!=0) {
    printf("Thread2 could not be created \n");
    return -1;
  }
  //printf("joined >>>>>>>>>>>>>>>>\n");
  int joined = pthread_join(thread1,&status);
  if (joined != 0) {
    printf("Error on thread1 \n");
    return -1;
  }
  //printf("joined2 >>>>>>>>>>>>>>>>>>>>>\n");
  int joined2 = pthread_join(thread2,&status);
  if(joined2 != 0){
    printf("Error on thread2\n" );
    return -1;

  }
  printf("Done \n");
  //create pthread for consumer
  return 0;
}
void *producer(void*param) {
  const char* string1 = "that";
  const char* string2 = "or ";

  /* pointer to shared memory object */
  char *path = param;
  void* ptr_to_sharedMem;
  int shm_fd = shm_open(path,O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, MEM_SIZE * sizeof(int));
  int *buffer = mmap(0,MEM_SIZE*sizeof(int),PROT_WRITE,MAP_SHARED,shm_fd,0);
  while (1) {
    if (_index < MEM_SIZE) {
      printf("Producer %d\n",_index );
      buffer[_index] = 1;
      _index++;
    }
  }
  shm_unlink(path);
  pthread_exit(NULL);
}


void *consumer(void *param/* arguments */) {
  /* code */
  char *path = param;
  void *ptr_to_sharedMem;
  //open file object
  int shm_fd = shm_open(path,O_CREAT | O_RDWR,0666);
  int *buffer = mmap(0,MEM_SIZE*sizeof(int),PROT_WRITE,MAP_SHARED,shm_fd,0);
  while (1) {
    /* code */
    if (_index > 0) {
      printf("consumer %d\n", _index);
      _index--;
      buffer[_index] = 99;
    }
  }
  shm_unlink(path);
  pthread_exit(NULL);
}
