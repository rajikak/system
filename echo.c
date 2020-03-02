#include <stdio.h>

int main(int argc, char* argv[]){

	char **p;
	for(p = argv; *p != NULL;p++){
		printf("%s\n", *p);
	}
	return 0;
}
