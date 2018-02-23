#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
        int fd;

        fd = open("destination.txt", O_CREAT | O_WRONLY, 0600);

        if(fd == -1)
        {
        printf("Failure to create file");
        exit(1);
        }
        close(fd);
return 0;
}
