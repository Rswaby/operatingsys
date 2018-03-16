#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[0])
{	
	execv("/bin/echo",&argv[0]);
	printf("EXECV Failed\n");
	// the above line will be printed only on error and not otherwise
}
