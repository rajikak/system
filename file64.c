/* large file */
#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>
#include "hdr.h"

#ifdef __APPLE__
#	define off64_t off_t
# 	define fopen64 fopen
#endif

int main(){

	const char *f = "tmp.txt";

	int fd = open64(f, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		fprintf(stderr, "open64 error, errno=%d\n", errno);
		return -1;
	}
	const int n = 1000000000;
	if(lseek64(fd, n, SEEK_SET) == -1){
		fprintf(stderr, "lseek64 error, errno=%d\n", errno);
		retunr -1;
	}
	if(write64(fd, "hello", 5) == -1) {
		fprintf(stderr, "write64 failed, errno=%d\n", errno);
		return -1;
	}

	return 0;
}
