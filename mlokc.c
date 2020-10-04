#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/errno.h>

int main(){

	long pgsz = sysconf(_SC_PAGESIZE);
	size_t len = 3 * pgsz;

	void *ptr = malloc(len);

	if(ptr == NULL) {
		fprintf(stderr, "malloc errro, errno:%d\n", errno);
		return -1;
	}

	if(mlock(ptr, len) != 0) {
		fprintf(stderr, "lock failed, errno:%d\n", errno);
		return -1;
	}
	printf("page lock area, memory is in RAM, not in VM\n");

	munlock(ptr, len);
	printf("unlocked\n");
}
