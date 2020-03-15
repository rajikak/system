#include <string.h>
#include "hdr.h"

#define BUF_SIZE 100

char extern **environ;

void printenv();

int main(int argc, char *argv[]){

	char buf[BUF_SIZE] = "";
	int len = 0;

	if(argc < 2) {
		fprintf(stderr, "usage error\n");
		return 0;
	}

	len = strlen(argv[1]) + strlen(argv[2]) + 1; /* 1 for '=' */
	if(len > sizeof(buf) - strlen(buf)){
		fprintf(stderr, "buffer would be truncated\n");
		return -1;
	}

	strncat(buf, argv[1], sizeof(buf) - strlen(buf) - 1);
	strncat(buf, "=", sizeof(buf) - strlen(buf) - 1);
	strncat(buf, argv[2], sizeof(buf) - strlen(buf) - 1);

	if(putenv(buf) == -1) {
		fprintf(stderr, "putenv error, errno=%d\n", errno);
		return -1;
	}

	printenv();
}

void printenv(){

	char **ep;

	for(ep = environ;*ep != NULL; ep++){
		printf("%s\n", *ep);
	}
}


