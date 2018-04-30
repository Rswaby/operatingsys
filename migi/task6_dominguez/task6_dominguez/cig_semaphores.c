//MIGUEL DOMINGUEZ
//TASK 6
//CIgarrete SMokers problem (SEMAPHORE)

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
#include <time.h>


//using std::cout;
//using std::endl;
//using std::string;
//using namespace std;


//THe following grants read and write permissions
#define PERMS 0666 

main()
{

	// semaphores for tabacco, paper and match smoker			
	int tabaco; //smoker with tabacco
	int paper;  //" " paper material
	int match;  // " " match material
	int agent;  //agent has infinite supply of any of the 3 materia;s
	int locker; // for lock semaphore
	

	//start creating semaphores and check if they are correctly created
	if((tabaco = semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1 ||
	   (paper  = semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1 ||
	   (match  = semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1 ||
	   (agent  = semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1 ||
	   (locker = semget(IPC_PRIVATE,1,PERMS | IPC_CREAT)) == -1)
	{
		printf("ONE OF THE SEMAPHORES HAS FAILED TO BE CREATED");
		//print above when sempahore is not created
	}

	//call sem_create and pass the intval parameter
	sem_create(tabaco,0);
	sem_create(paper,0);
	sem_create(match,0);
	sem_create(agent,0);
	sem_create(locker,1);


	int offspring; //used to fork purposes

	if((offspring = fork()) < 0)
	{
		printf("Failed to fork offspring");
	}
	else if(offspring == 0) //THe smoker with tabacco needs agent to provide the 2 missing materials
	{
		while(1)
		{
			//P() is the point of entry for semaphore
			//tabacco smoker sleeps 
			P(tabaco);
			P(locker); //enter locker
			V(agent);  //obtain other two materials
			V(locker);
			printf("Smoker with tabacco has obtained paper and match. \n");
		}
	}


	if((offspring = fork()) < 0)
	{
		printf("Failed to fork offspring");
	}
	else if(offspring == 0) //THe smoker with paper needs agent to provide the 2 missing materials
	{
		while(1)
		{
			//P() is the point of entry for semaphore
			//paper smoker sleeps 
			P(paper);
			P(locker); //enter locker
			V(agent);  //obtain other two materials
			V(locker);
			printf("Smoker with paper has obtained tabaco and match. \n");
		}
	}


	if((offspring = fork()) < 0)
	{
		printf("Failed to fork offspring");
	}
	else if(offspring == 0) //THe smoker with match needs agent to provide the 2 missing materials
	{
		while(1)
		{
			//P() is the point of entry for semaphore
			//match smoker sleeps 
			P(match);
			P(locker); //enter locker
			V(agent);  //obtain other two materials
			V(locker);
			printf("Smoker with match has obtained tabaco and paper. \n");
		}
	}

	srand ( time(NULL) ); //used for randomness when running the procedures
	int random_number; //it will keep a value, either 0, 1 or 2

	//Here we use randomness so that agen is placing two ingredients randomly 
	//for any smoker that gets back from sleep 
	 for (int i = 0; i < 10; i++)
	 {
		//each iteration produces a random number
		random_number = rand() % 3; 
		P(locker);
		
		if (random_number == 0)
		{
			printf("Agent has provided paper and match, smoker with tabaco is ready to smoke\n");
			//here we make smoker with tabacco wake up 
			V(tabaco);
		} 
		else if (random_number == 1)
		{
			printf("Agent has provided tabaco and match, smoker with paper is ready to smoke\n");
			//here we make smoker with paper wake up 
			V(paper); 
		}
		else if(random_number == 2)
		{
			printf("Agent has provided tabaco and paper, smoker with match is ready to smoke\n");
			//here we make smoker with paper wake up 
			V(match); 
		}
		V(locker);
		//agent goes to sleep in this part
		P(agent); 
	 }
	 return 0;
	//compile as gcc -o sem cig_semaphores.c
}


