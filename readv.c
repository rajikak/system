/* scatter i/o */
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "hdr.h"

#define STR_SIZE 100
#define IOV_BUF_SIZE 3


int main(){

	struct iovec iov[IOV_BUF_SIZE];
	struct stat my_strct; /* first buffer */
	int x;                /* second buffer */
	char str[STR_SIZE];   /* third buffer */
	ssize_t num_read, total_required;

	const char* f = "README.md";
	int fd = open(f, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "open error, errno = %d\n", errno);
		return -1;
	}

	total_required = 0;
	iov[0].iov_base = &my_strct;
	iov[0].iov_len  = sizeof(struct stat);
	total_required  += iov[0].iov_len;
	
	iov[1].iov_base = &x;
	iov[1].iov_len = sizeof(x);
	total_required += iov[1].iov_len;

	iov[2].iov_base = str;
	iov[2].iov_len = STR_SIZE;
	total_required += iov[2].iov_len;

	num_read = readv(fd, iov, IOV_BUF_SIZE);
	if(num_read == -1) {
		fprintf(stderr, "readv error, errno = %d\n", errno);
		return -1;
	}
	
	if (num_read < total_required) {
		printf("read fewer bytes than requested\n");
	}
	
	printf("total bytes requested = %ld, bytes read = %ld\n", (long)total_required, (long)num_read);
	return 0;	
}
