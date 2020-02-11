#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE !TRUE

int main(){
	
	const char *f = "tmp.txt";
	int n = 100000;
	int flag = TRUE;

	int fd;
	if(flag) {
		fd = open(f, O_RDWR | O_CREAT);
	} else {
		fd = open(f, O_CREAT | O_APPEND);
	}

	if(fd == -1) {
		fprintf(stderr, "open error, errno=%d\n", errno);
		return -1;
	}

	int written = 0;
	while (written <= n) {
		
		if(flag && lseek(fd, 1, SEEK_SET) == -1) {
			fprintf(stderr, "lseek failed, errno=%d", errno);
			return -1;
		}

		if(write(fd, "h" , 1) != 1) {
			fprintf(stderr, "write failed, errno=%d\n", errno);
			return -1;
		}
		written++;
	}
}
