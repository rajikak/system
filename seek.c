#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>


int main(){

	const char *f = "tmp.txt";
	int fd = open(f, O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if(fd == -1){
		fprintf(stderr,"open error, errno=%d\n", errno);
		return -1;
	}
	if(lseek(fd, 0, SEEK_SET) == -1){
		fprintf(stderr, "lseek error, errno=%d\n", errno);
		return -1;
	}
	if(write(fd, "lseek", 5) == -1) {
		fprintf(stderr, "write failed, errno=%d\n", errno);
		return -1;
	}

	return 0;
}
