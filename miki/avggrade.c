//Thanachot Sirifuangwattana
//Average Grade
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//director process created
	int x = 2; //number of chapters
	int y = 2; //number of hw
	int total= x*y; //total number of homeworks
	int grades[10][total]; //grades store in 2 dimensional array

	FILE *open; //open file containing grades of student
	open = fopen ("quiz_grades.txt", "r"); //open the file only to read the data

	int grade = 0;
	int i, j;

	//storing grades for 10 rows
	for(i = 0; i < 10; i++)
	{
		//for each grade
		for(j = 0; j < total; j++)
		{
			//get the value from the text and store each grade.
			fscanf(open, "%d", &grade);
			grades[i][j] = grade;
		}
	}
	fclose(open);

	//manager worker processes
	int manager, worker;

	//total grade for each students
	double scores = 0;

	for(i=0; i < x; i++)
	{
		//for every manager, create a manager(fork)		
		manager = fork(); 
		//if fork successful, otherwise display an error
		if(manager < 0)
		{
            		printf("error, no manager");
		}
		else if(manager == 0)
		{
			for(j = 0; j < y; j++)
			{
				//for every manager, creates worker
				worker = fork(); 
				if(worker < 0)
				{
                    			printf("error, no worker");
				}
				else if(worker == 0)
				{
                    			int s;
					for(s = 0; s < 10; s++)
					{
						//find the total grade for every students
						scores = scores + grades[s][i*y + j]; 
					}
					double average;
					average = scores/10;
					//take the average by dividing 10
					printf("%f \n", average); 
					return 0;
				}
				wait(&worker);
			}
			return 0;
		}
		wait(&manager);
	}
	return 0;
}

