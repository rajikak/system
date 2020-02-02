#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <unistd.h>

int main(){

	const char *f = "tmp.txt";

	int fd = open(f, O_EXCL|O_CREAT);
	if(fd == -1){
		printf("file already exists\n");
		close(fd);
	} 

	int flags = fcntl(fd, F_GETFL);
	if(flags == -1){
		fprintf(stderr,"fcntl failed, errno=%d\n", errno);
		return -1;
	}
	printf("flags=%d\n", flags);
}
