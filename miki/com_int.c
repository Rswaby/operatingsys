//Thanachot Sirifuangwattana
//Command interpreter
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;    //child named pid
	char input[100]; //line input
	char *insert;   //location to be inserted
	char *args[20]; //number of arguments
	int comparison;

	while(1)
	{
        	//command options
        	printf("enter command, else exit: ");
        	scanf("%[^\n]", input);

        	//checking if user input quit, if so, exit the program.
        	comparison = strcmp(input,"quit");
        	if(comparison == 0)
        	{
            		return 0;
        	}

        	//if else not exit, check for arguements
        	insert = strtok(input, " ");
        	args[0] = insert;

        	//sotring strings to args
        	for (int i = 1;i < 20; i++)
        	{
            		insert = strtok(NULL, " ");
            		args[i] = insert;
        	}

        	//child will be forked
        	pid = fork();
        	if (pid < 0)
        	{
        		printf("error, unable to fork\n");
        	}
        	else if (pid == 0)
        	{
        		execvp(args[0], &args[0]);
        		return 0;
        	}
        	wait(&pid);
	}
	printf("finish.\n");
	return 0;
}
