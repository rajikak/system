/* basic malloc() and free() for `char` type */
#include "hdr.h"

typedef struct node {
	size_t len;
	node *prev;
	node *next;
	char *buffer;
}

char *malloc(size_t size, node *free_list){
	/* build free list */
}

void free(char *ptr, node *free_list){

}


int main() {
	
	node *l = NULL;
	char *p1, *p2, *p3;

	p1 = malloc(5, l); /* "hello" */
	p2 = malloc(5, l); /* "world" */

	p1 = "hello";
	p2 = "world";

	printf("%s\n", p1);
	printf("%s\n", p2);

	free(p1);
	free(p2);

	return 0;
}

