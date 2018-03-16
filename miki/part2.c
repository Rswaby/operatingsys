//MIGUEL DOMINGUEZ
//TASK 4
//PART 2 AVERAGE GRADE CALCULATOR

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;
using namespace std;

int main (int argc, char* argv[])
{
	//This is the Director in charge. 
	int score = 0;		//Each individual score
	int chapters = 2;	//For x number of chapters
	int homeworks = 2;	//FOr y number of homeworks for each chapter
	int students = 10;
	int sum = 0; 		//SUm of scores for each homework
	int status; 		//Status word for waiting
	int grades[students][chapters*homeworks];
	
	//PROCESS TEXT FILE
	FILE *openfile; //THis is to open a text file
	openfile = fopen ("scores.txt", "r"); //this  is to set read mode for text file
	
	
	//SAVE GRADE DATA TO 2D ARRAY grade
	for(int i = 0; i < students; i++)
	{
		for(int j = 0; j < (chapters*homeworks); j++)
		{
			fscanf(openfile, "%d", &score); //get each grade score filling both rows and columns for grades
			grades[i][j] = score;
		}
	}
	fclose(openfile);

	//Start forking managers and workers accordingly
	for(int i = 0; i < chapters; i++)
	{
		int manager = fork(); //Forking manager for chapter
		if(manager == 0)
		{
			for(int j = 0; j < homeworks; j++)
			{
				int worker = fork(); //Forking worker for homework
				if(worker == 0)
				{
					for(int k = 0; k < students; k++)
					{
						sum = sum + grades[k][j]; //Add grades for particular homework 
					}
					//DO CALCULATIONS AND SHOW AVERAGE FOR THAT HOMEWORK
					int average = sum/students; 
					cout<<"Chapter" << i << " Homework " << j << " Average: "<<average<<endl;
					exit(worker);
				}
				else
				{
					int endID = waitpid(worker, &status,0);
				}

			}
			
		}
		else
		{
			int endID = waitpid(manager, &status,0);
		}

	}
	
	return 0;
}
