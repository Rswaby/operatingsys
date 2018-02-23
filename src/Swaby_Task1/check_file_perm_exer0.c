#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	char* filepath=argv[1];
	int returnval;

	//check file existence
	returnval = access (filepath, F_OK);
	int secondreturn;
	int readaccess = access (filepath, R_OK);
	int writeaccess = access (filepath, W_OK);
	printf("this is second return  %d",secondreturn);

	if(returnval == 0)
		printf("\n %s exists\n", filepath);
	else
	{
		if(errno == ENOENT)
			printf("%s doesn't exist\n",filepath);
		else if(errno == EACCES)
			printf("%s is not accessible\n",filepath);
		//return 0;
	}

	//check read access
	//.........
	//check write access
	//.....
	//

	if(readaccess == 0)
	  printf("\n %s has read access", filepath);
	
	else
	  {
	    printf("\n %s doesn't have read access",filepath);
	  }

	if(writeaccess == 0){
	  printf("\n %s has write access \n", filepath);
	}
	else{
	  printf("\n %s does not have write access \n", filepath);
	    }
	  

	
	return 0;
}
