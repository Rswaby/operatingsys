
//MIGUEL DOMINGUEZ
//TASK 4
//PART 1 SIMPLE COMMAND INTERPRETER

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

using std::cout;
using std::endl;
using std::string;
using namespace std;

int main (int argc, char* argv[])
{

	bool run = true;  //When true we keep the terminal running
	char command[100]; //holds input command
	char *arguments[20]; //arguments for fuction excvp
	char *token; //Used to hold tokens
	int status; //Use to wait

	while(run)
	{
		cout<<"Please insert a terminal command (i.e date, ls): "<<endl;
		cout<<"Enter STOP to end terminal interface."<<endl;
		cin >> command;
		//cout<<command<<endl;
		if(command[0] == 'S' && command[1] == 'T' && command[2] == 'O' && command[3] == 'P')
		{
			cout<<"Program Terminated"<<endl;
			run = false;
			break;
		}

		//We will tokenize our command separating it by whitespacing
		token = strtok(command, " ");
		arguments[0] = token;
		
		//Keep tokenizing command into respective arguments
        	for (int i = 1;i < 20; i++)
        	{
            		token = strtok(NULL, " ");
            		arguments[i] = token;
        	}

		//At this point we are ready to fork a child process
		int offspring = fork(); //FOrk child process

		if(offspring == 0)
		{
			cout<< "Executing command, PID: " << getpid() <<endl; 
			cout<<"============"<<endl;
			execvp(arguments[0], &arguments[0]); //Execute given argument
			
		}
		else
		{
			int endID = waitpid(offspring, &status,0);
			cout<<"============"<<endl;
			cout<<"Command executed, PID: " << endID <<endl; 
			cout<<endl;
			cout<<endl;
		}
	}
	
	cout<<"No longer in terminal."<<endl;

	return 0;

	/* EXAMPLES USING THE PROGRAM:

	Please insert a terminal command (i.e date, ls): 
	Enter STOP to end terminal interface.
	ls
	Executing command, PID: 2674
	============
	part1  part1.c	part1.o
	============
	Command executed, PID: 2674


	Please insert a terminal command (i.e date, ls): 
	Enter STOP to end terminal interface.
	date
	Executing command, PID: 2675
	============
	Wed Oct 25 21:23:13 EDT 2017
	============
	Command executed, PID: 2675

	*/

}



