//MIGUEL DOMINGUEZ
//TASK 6
//CIgarrete SMokers problem (THREADS)

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//#include <iostream>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include "sem.h"
#include <pthread.h>
#include <time.h>


//using std::cout;
//using std::endl;
//using std::string;
//using namespace std;

//thread initializer
pthread_mutex_t lock   = PTHREAD_MUTEX_INITIALIZER;

//pointer fuctions for smokers and agents
void *tabaco_f();
void *paper_f();
void *match_f();
void *agent_f();

//create instances of semaphores
sem_t tabaco;
sem_t paper;
sem_t match;
sem_t agent;

//flag variable used to check if agent has terminated
int flag = 1;

main()
{
     //declare four threads called tre
     pthread_t tre0;
     pthread_t tre1; 
     pthread_t tre2; 
     pthread_t tre3; 

     //the following is for the return values from threads
     int ret0;
     int ret1;
     int ret2;
     int ret3;
	
     //initalize the semaphores and pass initial values 
     sem_init(&tabaco, 0, 0);
     sem_init(&paper, 0, 0);
     sem_init(&match, 0, 0);
     sem_init(&agent, 0, 0);

     srand ( time(NULL) ); //used for randomness when running the procedures
	 
     //create all independtent treads and their corresponsing functions
     ret0 = pthread_create( &tre0, NULL, agent_f, NULL);
     ret1 = pthread_create( &tre1, NULL, tabaco_f, NULL);
     ret2 = pthread_create( &tre2, NULL, paper_f, NULL);
     ret3 = pthread_create( &tre3, NULL, match_f, NULL);
     
     //check errors or failrs to create threads
     if(ret0 || ret1 || ret2 || ret3)
     {
         printf("ERROR FOR THREAD, CHECK RETURN FOR THREADS\n");
     }
	 
     //wait for completion of treads
     pthread_join(tre0, NULL); 
	 
     //when agent is executing, cancel other agents
     if (flag == 0)
     {
	 pthread_cancel(tre1);
	 pthread_cancel(tre2);
	 pthread_cancel(tre3);
     }
	 
     pthread_join(tre1, NULL);
     pthread_join(tre2, NULL); 
     pthread_join(tre3, NULL); 

     exit(EXIT_SUCCESS);
     //compile as gcc -o tre cig_treads.c
}

//agent f
void *agent_f()
{
	for (int i = 0; i<10; i++)
	{	
		pthread_mutex_lock(&lock);
		//each iteration produces a random number, either 0,1,2
		int random_number = rand() % 3; 
		if (random_number == 0)
		{
			printf("Agent has provided paper and match, smoker with tabaco is ready to smoke\n");
			//here we make smoker with tabacco wake up 
			sem_post(&tabaco); 
		} 
		else if (random_number == 1)
		{
			printf("Agent has provided tabaco and match, smoker with paper is ready to smoke\n");
			//here we make smoker with paper wake up 
			sem_post(&paper);
		}
		else if (random_number == 2)
		{
			printf("Agent has provided tabaco and paper, smoker with match is ready to smoke\n");
			//here we make smoker with paper wake up 
			sem_post(&match); 
		}
		pthread_mutex_unlock(&lock);
		//agent goes to sleep in this part
		sem_wait(&agent); 
	}
	 flag = 0; //when the tread for agent is finished, we need set it to zero to inducate such
}

//tabaco_f
void *tabaco_f()
{
	while (1)
	{
		//tabacco smoker sleeps
		sem_wait(&tabaco);  
		pthread_mutex_lock(&lock);
		sem_post(&agent);//obtain other two materials
		pthread_mutex_unlock(&lock);
		printf("Smoker with tabacco has obtained paper and match. \n");
	}
}

//paper_f
void *paper_f()
{
	while(1)
	{
		//paper smoker sleeps
		sem_wait(&paper); 
		pthread_mutex_lock(&lock);
		sem_post(&agent);//obtain other two materials
		pthread_mutex_unlock(&lock);
		printf("Smoker with paper has obtained tabaco and match. \n");
	}
}

//match_f
void *match_f()
{
	while (1)
	{
		//match smoker sleeps
		sem_wait(&match);  
		pthread_mutex_lock(&lock);
		sem_post(&agent);
		pthread_mutex_unlock(&lock); //obtain other two materials
		printf("Smoker with match has obtained tabaco and paper. \n");
	}
}

//to compile and run
// gcc smokerthread.c -o cat -lpthread

