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
	int a = 10, b = 25, fq = 0, fr = 0;
	fq = fork(); // fork a child - call it process Q

	if(fq == 0) //we are now in the child proccess 
	{
		a = a+b;
		printf("a: %d, b: %d, process id: %d \n",a, b,getpid());
		fr = fork();
		if(fr!=0)
		{
			b=b+20;
			printf("a: %d, b: %d, process id: %d \n",a, b,getpid());
		}else{
			a = (a*b)+30;
			printf("a: %d, b: %d, process id: %d \n",a, b,getpid());

		}

	}else{
		b=a+b-5;
		printf("a: %d, b: %d, process id: %d \n",a, b,getpid());

	}

	return 0;
}