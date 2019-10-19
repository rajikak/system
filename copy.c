#include <sys/stat.h>
#include <fcntl.h>
#include "hdr.h"

#ifndef BUF_SIZE /* override -DBUF_SIZE*/
#define BUF_SIZE 500
#endif

int main(int argc, char *argv[]) {

	int input_fd, out_fd, open_flags;
	mode_t file_params;
	ssize_t num_read;
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		fprintf(stderr, "%s old new\n", argv[0]);
		return -1;
	}

	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1) {
		fprintf(stderr, "opening file %s\n", argv[1]);
		return -1;
	}
	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_params = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
		S_IROTH | S_IWOTH;
	out_fd = open(argv[2], open_flags, file_params);
	if (out_fd == -1) {
		fprintf(stderr, "opening file %s\n", argv[2]);
		return -1;
	}
	
	while((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
		if(write(out_fd, buf, num_read) != num_read){
			fprintf(stderr, "cloud not write whole buffer\n");
			return -1;
		}
	}
	if (num_read == -1){
		fprintf(stderr, "read error\n");
		return -1;
	}
	if (close(input_fd) == -1) {
		fprintf(stderr, "close input\n");
	}
	if (close(out_fd) == -1) {
		fprintf(stderr, "close o/p\n");
	}

	exit(EXIT_SUCCESS);
}
