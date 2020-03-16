#include "hdr.h"

char extern **environ;

void printenv() {
	char **ep;
	for(ep = environ; *ep != NULL; ep++){
		printf("%s\n", *ep);
	}
}

int index2(char *s){

	char *v;
	int index;
	for(v = s,index = 0; *v != '\0';v++,index++){
		if(*v == '='){
			return index;
		}
	}
	return -1;
	
}

int main(int argc, char *argv[]) {

	char **ep;
	int loc;
	if(argc < 2) {
		fprintf(stderr, "usage error\n");
		return -1;
	}

	printenv();

	for(ep = environ;*ep != NULL; ep++){
		loc = index2(*ep);
		*ep[loc] = '\0';	
		if(loc != -1 && putenv(*ep) == -1) {
			fprintf(stderr, "putenv failed, errno=%d\n", errno);
			return -1;
		}
	}	

	printenv();
}
