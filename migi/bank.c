//MIGUEL DOMINGUEZ
//TASK 5
//FAther and Son program bank

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


//using std::cout;
//using std::endl;
//using std::string;
//using namespace std;

#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

int *waitfather, *waitson1, *waitson2; //waiting time pointers



main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	int fatherpid;  //THose variables are to store the pids that must be shown
	int son1pid;
	int son2pid; 
	int loc1;      //This is to direct the pointers direction where such are saved
	int loc2;
	int loc3; 
	waitfather = &loc1;
	waitson1 = &loc2;
	waitson2 = &loc3;

	//At this point we are ready to use the semaphore 
	//which are useful for preventing race conditions
	//over a shared resorce
	int semaphore = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
	sem_create(semaphore,1);
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=5;
		for(i=1;i<=N; i++)
		{
			P(semaphore); //THis means that we are entering the critical section
			//From my understanding both sons here are waiting
			//meanings that they would like to enter the critial senction
			//however other processes is using such resorce for the waiting
			//time is added to both sons. 
			if (son1pid != 0)
            		{
                		*waitson1 = loc2 + 1; //add time
            		}
            		if (son2pid != 0)
            		{
                		*waitson2 = loc3 + 1; //add time
            		}

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */
			V(semaphore); //THis is the exit for the critical section meaning that it now is open to other procresses
			//that have been waiting to enter the critical section 
		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{
				son1pid = getpid();
				P(semaphore); 
				//WIth the line above we enter the critical section again but for this time
				//it is the prorcess for the son 1
				if(fatherpid != 0)
                		{
                   		 	*waitfather = loc1 + 1; //add time
               			}
                		if(son2pid != 0)
                		{
                    			*waitson2 = loc3 + 1; //add time
                		}

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				V(semaphore); //Againt once we enter we must exit the critical section 
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					son2pid = getpid();  
				    	P(semaphore);      
				    	//We enter the critical section again but this time we are checking for the pids
					//of the father and child 1 which is the opposive of what we did for the other child
					//we always add on time while we wait
				    	if(fatherpid != 0)
                    			{
                       				 *waitfather = loc1 + 1; //add time
                    			}
                    			if(son1pid != 0)
                    			{
                        			*waitson1 = loc2 + 1; //add time
                    			}

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					V(semaphore); //exit the critical section for this case as well
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
				semkill(semaphore); //this last statement is to get rid of the semaphore since
				//the parent process awaits for the execution of each of his childs to finish 
				//this means that when no longer needed it is safe to delete it 
	
				
			}
			exit(0);
		}
		//tHIS will display the waiting times for the father and the childs at the end of the program
		printf("Waiting time father : %d\n", *waitfather);
		printf("WAiting time son1 : %d\n", *waitson1);
		printf("Waiting time son2 : %d\n", *waitson2);
		exit(0);
	}
	exit(0);
} //compile it as gcc -o run bank.c




