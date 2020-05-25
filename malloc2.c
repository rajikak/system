/* basic malloc() and free() for `char` type */
#include "hdr.h"

typedef struct node {
	size_t len;
	struct node *prev;
	struct node *next;
	char *buf;
} node_t;

/* head of free list(list of memory free by free) */
static node_t *head; 

char *malloc2(size_t size){
	char *p;
	/* build free list, a more efficient allocator can move the 
	 * break point in much bigger chunks than requested.*/
	printf("program break: %10p\n", sbrk(0));
	if (head == NULL) {
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
		head = &e;

		printf("break now    : %10p\n", sbrk(0));
		return e.buf;
		
	} else {
		/* best fit allocator */
		node_t *tmp = head;
		while(tmp != NULL) {

			if(tmp->len > size) {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				printf("program break(after allocation-best fit): %10p\n", sbrk(0));
				return tmp;
			}	

			tmp = tmp->next;		
		}

		node_t e;
		e.len = size;
		e.prev = head->next;
		e.next = NULL; /* tail */
		p = (char *)sbrk(size + 1);
		if ( p == (char *) -1) {
			fprintf(stderr, "sbrk failed, errono=%d\n", errno);
			return NULL;
		}

		e.buf = p;
		tmp->next = &e;

		printf("program break(after allocation): %10p\n", sbrk(0));
		return e.buf;
	}
}

void free2(char *ptr){
	node_t *tmp = head;

	/* double free is seg fault */
	while(tmp != NULL) {
		tmp->next = 		

		tmp = tmp->next;
	}
}


int main() {
	
	char *buf1, *buf2;

	buf1 = malloc2(5); /* "hello" */
	buf2 = malloc2(5); /* "world" */

	printf("buf1: %10p\n", buf1);
	printf("buf2: %10p\n", buf2);

	memcpy(buf1, "hello", 5);
	memcpy(buf2, "world", 5);

	free2(buf1);
	free2(buf2);

	/* seg fault, double free */
	printf("%s\n", buf1);

	return 0;
}

