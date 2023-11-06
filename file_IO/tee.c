#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUF_SIZE
#define BUF_SIZE		1024
#endif

typedef enum{
	TRUE = 1,
	FALSE = 0,
} Bool;

int main(int argc, char *argv[]){
	int fd;
	ssize_t numRead;
	char buffer[BUF_SIZE];
	char opt;
	Bool append = FALSE;
	int flag = 0;
	mode_t mode;

	while((opt = getopt(argc, argv, "ah")) != -1){
		switch(opt){
			case '?':
				printf("Wrong syntax\n");
				printf("Usage: %s [-a] <file_name>\n", argv[0]);
                                return 0;
			case 'h':
				printf("Usage: %s [-a] <file_name>\n", argv[0]);
				return 0;
			case 'a':
				append = TRUE;
				break;
		}
	}
	if(append){
		flag = O_WRONLY | O_APPEND | O_CREAT;
	}else{
		flag = O_WRONLY | O_TRUNC | O_CREAT;
	}
	mode = S_IRUSR | S_IWUSR; /* rw------- */
	fd = open(argv[optind], flag, mode);
	if(fd < 0){
		printf("Cannot open %s\n", argv[optind]);
		return -1;
	}
	while((numRead = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0){
		if(write(STDOUT_FILENO, buffer, numRead) != numRead){
			printf("Cannot write\n");
			return -1;
		}
		if(write(fd, buffer, numRead) != numRead){
			printf("Cannot write\n");
			return -1;
		}
	}
	if(numRead = read(STDIN_FILENO, buffer, BUF_SIZE) < 0){
		printf("Cannot read\n");
		return -1;
	}

	close(fd);

	return 0;
}
