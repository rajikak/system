/* gcc -g -Wall -Werror -ansi -pedantic unsetenv.c -o unsetenv */
#include "hdr.h"

char extern **environ;

void printenv() {
	char **ep;
	for(ep = environ; *ep != NULL; ep++){
		printf("%s\n", *ep);
	}
}

int index2(char *s){

	int ch;
	for(ch = 0; s[ch] != '\0';ch++){
		if(s[ch] == '='){
			return ch;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) {

	char **ep, *token, buf[100];
	const char sep[2] = "=";

	if(argc < 2) {
		fprintf(stderr, "usage error\n");
		return -1;
	}

	printenv();

	for(ep = environ;*ep != NULL; ep++){
		token = strtok(*ep, sep);

		if(strcmp(token, argv[1]) != 0) {
			continue;	
		}

		memset(buf, '\0', sizeof(buf));
		if(strcpy(buf, *ep) == NULL) {
			fprintf(stderr, "strcpy failed, errno=%d\n", errno);
			return -1;
		}
		printf("matched: %s, %s\n", buf, getenv(buf));	
	}	
	printenv();
}
