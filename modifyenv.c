#define _GNU_SOURCE
#include <stdlib.h>
#include "hdr.h"

extern char **environ;

int main(int argc, char *argv[]){
	int j;
	char **ep;

	clearenv();

	for(j = 1;j < argc;j++) {
		if(putenv(argv[j]) != 0) {
			fprintf(stderr, "putenv failed, errno=%d\n", errno);
			return -1;
		}
	}

	if(setenv("GREET", "hello, world!", 0) == -1){
		fprintf(stderr, "setenv failed, errno=%d\n", errno);
		return -1;
	}
	
	unsetenv("BYE");

	for(ep = environ; *ep != NULL; ep++) {
		printf("%s\n", *ep);
	}
	return 0;
}
