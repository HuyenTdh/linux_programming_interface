#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif /* BUF_SIZE */

int main(int argc, char *argv[])
{
	int oldFd;
	int newFd;
	int openFlag;
	mode_t modeFd;
	char buffer[BUF_SIZE];
	ssize_t numRead;

	if((argc != 3) || (strcmp(argv[1], "--help") == 0)){
		printf("%s old_file new_file\n", argv[0]);
		return -1;
	}

	oldFd = open(argv[1], O_RDONLY);
	if(oldFd < 0){
		printf("Cannot open %s\n", argv[1]);
		return -1;
	}

	openFlag = O_WRONLY | O_CREAT | O_TRUNC;
	modeFd = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
	newFd = open(argv[2], openFlag, modeFd);
	if(newFd < 0){
                printf("Cannot open %s\n", argv[2]);
                return -1;
        }

	while((numRead = read(oldFd, buffer, BUF_SIZE)) > 0){
		if(write(newFd, buffer, numRead) != numRead){
	                printf("Cannot write whole buffer\n");
        	        return -1;
        	}
	}
	if(numRead < 0){
                printf("Cannot read\n");
                return -1;
        }
	if(close(oldFd)){
                printf("Cannot close %s\n", argv[1]);
                return -1;
        }
	if(close(newFd)){
                printf("Cannot close %s\n", argv[2]);
                return -1;
        }
	
	return 0;
}
