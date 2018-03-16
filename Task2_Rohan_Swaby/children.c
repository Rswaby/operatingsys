#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{

	int status;
	pid_t pid;																																																																
	int child = fork();
	pid = waitpid(child,&status,0);
	if(child == 0)
	{
		int id = getpid();
		printf("Parent: %d\n", getppid());
		printf("I am child one with pid %d\n",id );
	}

	else if(child < 0)
	{
		perror("fork() error");
		return -1;

	}
	else{
		
		int child2 = fork();
		pid = waitpid(child2,&status,0);
		if(child2 == 0)
		{
			int pid2 = getpid();
			printf("Parent: %d\n", getppid());
			printf("I am child two with pid %d \n", pid2);
		}

		else{
			printf("End of parent %d \n", getpid());
		}
		//create a parent process here using waitpid


	}

	return 0;
}