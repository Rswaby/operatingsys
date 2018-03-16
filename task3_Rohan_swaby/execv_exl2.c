#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{	
	execvp("echo",&argv[0]);
	printf("EXECVP Failed\n");
	//The above line will be printed only on error and not otherwise
}
