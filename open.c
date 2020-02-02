/* open bug */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>

int main(){

	const char *f = "tmp.txt";
	int fd = open(f, O_WRONLY); /* int fd = open(f, O_EXCL | O_CREAT); */
	if(fd != -1) {
		printf("[pid %ld] file %s already exists\n", (long)getpid(), f);
		close(fd);
	} else {
		if(errno != ENOENT) {
			fprintf(stderr, "open failed, errno=%d\n", errno); /* open failed for unknow reason */
			return -1;
		} else {
			fd = open(f, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			if (fd == -1) {
				fprintf(stderr, "open failed\n");
				return -1;
			}
			/* below line is buggy, may not be true, because first open() didn't use the flag
			   O_EXCL | O_CREATE for atomicity */
			printf("[pid %ld] created file %s execlusively\n", (long)getpid(), f);
		}
	}

}
