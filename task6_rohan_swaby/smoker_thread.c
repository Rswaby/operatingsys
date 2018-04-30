//Rohan Swaby
//solution to the smokers problems using pthreads
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include "sem.h"
#include <pthread.h>
#include <time.h>
//init thread
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


//materials for smokers
void *tabaco();
void *paper();
void *match();
void *agent();

sem_t tabaco_sem;
sem_t paper_sem;
sem_t match_sem;
sem_t agent_sem;

int flag = 1;// is agent terminated 
int main(int argc, char const *argv[])
{

  pthread_t thread1,  thread2, thread3, thread4;


  int return1,return2,return3,return4;

  sem_init(&tabaco_sem,0,0);
  sem_init(&paper_sem,0,0);
  sem_init(&match_sem,0,0);
  sem_init(&agent_sem,0,0);

  srand( time(NULL)); //used to randomize stuff
  //creating threads for agent, tabaco,paper, match
  return1 = pthread_create ( &thread1, NULL, agent, NULL);
  if(return1) printf("thread1 failed creation. \n");//
  
  return2 = pthread_create ( &thread2, NULL, tabaco, NULL);
  if(return2) printf("thread2 failed creation. \n");//
  
  return3 = pthread_create ( &thread3, NULL, paper, NULL);
  if(return3) printf("thread3 failed creation. \n");//
  
  return4 = pthread_create ( &thread4, NULL, match, NULL);
  if(return4) printf("thread4 failed creation. \n");//

  pthread_join(thread1, NULL);

  if(flag == 0)
    {
      pthread_cancel(thread2);
      pthread_cancel(thread3);
      pthread_cancel(thread4);
    }

  pthread_join(thread2 NULL);
  pthread_join(thread3 NULL);
  pthread_join(thread4 NULL);

  return 0;
}

void *tabaco(){

  while(1)
    {
      sem_wait(&tabaco_sem);
      pthread_mutex_lock(&lock);
      sem_post(&agent_sem);
      pthread_mutex_unlock(&lock);
      printf("Smoker with tabaco has obtained paper and match. \n");

    }
}

void *paper(){
  while(1)
  {
    sem_wait(&paper_sem);
    pthread_mutex_lock(&lock);
    sem_post(&agent);
    pthread_mutex_unlock(&lock);
    printf("Smoker with paper just got tabacco and match. \n");
  }
}

void *agent()
{
  int n = 10
    while( n > 0){

  pthread_mutex_lock(&lock);

  int random_number = rand() % 3;

  if(random_number == 0){
    print("Agent placed match and paper on table \n");
    //wake up smoker
    sem_post(&tabaco_sem);
  }
  else if (random_number == 1){
    printf("Agent placed tobacco and match on table. \n");
    sem_post(&paper_sem);
  }
  else{
    printf("Agent placed tobacco and paper on table");
    sem_post(&match_sem);
  }

  pthread_mutex_unlock(&lock);

  sem_wait(&agent_sem);
  n--;


    }
  flag = 0;
  
}

