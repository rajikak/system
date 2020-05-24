/* basic malloc() and free() for `char` type */
#include "hdr.h"

typedef struct node {
	size_t len;
	struct node *prev;
	struct node *next;
	char *buf;
} node_t;

char *malloc2(size_t size, node_t *flp){
	char *p;
	/* build free list */
	printf("program break: %10p\n", sbrk(0));
	if (flp == NULL) {
		node_t e;
		e.len  = size;
		e.prev = NULL;
		e.next = NULL;
		p = (char *)sbrk(size + 1); /* extra byte for '\0' */

		if (p == (char *) -1) {
			fprintf(stderr, "sbrk failed, errno=%d\n", errno);
			return NULL;
		}
		e.buf = p;
		return e.buf;
		
	} else {

	}
	printf("program break(after allocation): %10p\n", sbrk(0));
}

void free2(char *ptr, node_t *flp){

}


int main() {
	
	node_t *frlst = NULL;
	char *buf1, *buf2;

	buf1 = malloc2(5, frlst); /* "hello" */
	buf2 = malloc2(5, frlst); /* "world" */

	memcpy(buf1, "hello", 5);
	memcpy(buf2, "world", 5);

	printf("%s\n", buf1);
	printf("%s\n", buf2);

	free2(buf1, frlst);
	free2(buf2, frlst);

	/* seg fault, double free */
	printf("%s\n", buf1);

	return 0;
}

