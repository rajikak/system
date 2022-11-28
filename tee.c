#include <sys/stat.h>
#include <fcntl.h>
#include "hdr.h"

#ifndef BUF_SIZE /* override -DBUF_SIZE */
#define BUF_SIZE 500
#endif

int main(int argc, char *argv[]) {

	int out_fd, open_flags;
	mode_t file_params;
	ssize_t num_read;
	char buf[BUF_SIZE];

	if (argc != 2 || strcmp(argv[1],"--help") == 0) {
		fprintf(stderr, "%s tee file\n", argv[0]);
		return -1;
	}

	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_params = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	out_fd = open(argv[1], open_flags, file_params);

	if(out_fd == -1) {
		fprintf(stderr, "openning file %s\n", argv[1]);
		return -1;
	}

	for(;;){
		memset(buf, '\0', BUF_SIZE);
		char* s = fgets(buf, BUF_SIZE, stdin);
		if(s == NULL) { /* EOF */
			break;	
		}

		if(write(out_fd, buf, sizeof(buf)) == -1) {
			fprintf(stderr, "could not write whole buffer\n");
			return -1;
		}
		printf("%s", buf);
	}
}
