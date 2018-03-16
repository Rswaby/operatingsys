//Author: Rohan Swaby
//task4: compute the average of x chapters with y homeworks form each
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int countrows(char arr[],int size){
	int col = 0;
	int i = 0;
	for(i = 0; i < size; i++)
	{
	    printf("%s \n",&arr[i]);


	}

	return 0;
}

int main(int argc, char* argv[])
{
        //get amount of colums and rows from csv file
	int checkaveragefileaccess;
	int chapters = 5;
	int homeworks = 2;
	const int STUDENTS = 10;
	int _MAX = chapters*homeworks;//HOME WORK FOR EACH STUDENT
	int gradebook[STUDENTS][_MAX];
	int score;
	FILE* openave;
	int readaverage;
	double aveScore;



	if(argc < 2)
	{
	printf("missing file: please Enter a file to be read (i.e grades.txt \n");
	    return -1;
	}


	char* filepath = argv[1];
	printf("\n");
	printf("======================> Course Grade book <======================= \n");
	checkaveragefileaccess = access(filepath, F_OK);
	if(checkaveragefileaccess == -1)
	{
	    printf("File %s doesn't exit",filepath);
	    return -1;
	}

	//open text file.
	openave = fopen(filepath,"r");
	int i,j;

	//This block of code will get the data from the file into a 2d array
	for(i = 0; i<STUDENTS; i++)
	{

		for(j = 0; j<_MAX; j++)
		{
			//look at each digit in the file
			fscanf(openave,"%d",&score);
			//printf("i:%d, j:%d score: %d \n",i,j,score);
			gradebook[i][j]=score;

		}
	}
	fclose(openave);//

	//number of managers = the number of chapters;
	//number of e
	//number of workers = the number of hws for each chapter

	//start by forking a manager per chapter.
	int man;
	int child_worker;
	int status;
	int workerstatus;
	for(man = 0; man<chapters; man++)
	{
		//managers
		int manager = fork();//fork

		if(manager == 0)

		{
			//manager succesfully forked
			// in the manager process fork hw for each student

			for(child_worker = 0; child_worker<homeworks; child_worker++)
			{

				int worker = fork();

				if(worker==0)
				{


					//calculate average for
					//printf("worker %d : working \n" ,child_worker);
					// 2 4 5 6 6 (00)(01)(02)(03)(04)(05)
					// 2 4 5 6 7 (10)
					// 4 5 6 7 8 (20)
					// 2 4 6 7 8 (30)
					// 2 7 3 2 7 (40)
					// man*number_of_hw + worker---
					// 0 * 2 + 0 = 0
					// 0 * 2 + 1 = 1
					// 0 * 2 + 2 = 2
					int student;
					int sum = 0;
					double average;
					for(student = 0; student < STUDENTS; student++)
					{
						//test does this fomulat give me two columns per worker?
						sum += gradebook[student][man*homeworks+child_worker];

					}
					average = sum/STUDENTS;

					printf("|            Chapter: %d Homework %d Average: %f             | \n",(man+1), child_worker, average);

					return 0;
				}

				else
					waitpid(worker,&workerstatus,0);


			}


		}
		else
		{
			//this is the parent process
			//wait for the worker child process to finish
			waitpid(manager,&status,0);
			return 0;

		}


	}

	printf("============================> END <===============================\n");
	printf("\n");

	return 0;
}
