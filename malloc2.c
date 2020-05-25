/* malloc() and free() for `char` type */
#include "hdr.h"

typedef struct node {
	size_t len;
	struct node *prev;
	struct node *next;
	char   *buf;
} node_t;

/* free list */
static node_t *head; 

char *malloc2(size_t size){
	char *p;
	int counter = 0;
	printf("program break(counter=%d): %10p\n", counter++, sbrk(0));
	if (head == NULL) {
		p = (char *)sbrk(size + 2); /* extra two bytes for '\0' and size */
		if (p == (char *) -1) {
			fprintf(stderr, "sbrk failed, errno=%d\n", errno);
			return NULL;
		}
		*p = (char) size;
		printf("program break(counter=%d): %10p\n", counter++, sbrk(0));
		return p + 1;
		
	} else {
		/* first fit allocator */
		node_t *tmp = head;
		while(tmp != NULL) {

			if(tmp->len > size) {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				printf("program break(counter=%d): %10p\n", counter++, sbrk(0));
				return tmp->buf;
			}	

			tmp = tmp->next;		
		}

		p = (char *)sbrk(size + 2);
		if (p == (char *) -1) {
			fprintf(stderr, "sbrk failed, errono=%d\n", errno);
			return NULL;
		}

		*p = (char) size;
		printf("program break(counter=%d): %10p\n", counter++, sbrk(0));
		return p + 1;
	}
}

void free2(char *ptr){

	node_t e, *tmp;
	e.len = *(ptr - 1);
	e.next = NULL; /* tail */
	e.buf = NULL; /* derefrence */

	if (head == NULL){
		e.prev = NULL;
		head = &e;
	} else {
		/* append to free list */
		tmp = head;
		while(tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = &e;
		e.prev = tmp;
	}
	ptr = NULL;
}


int main() {
	
	char *buf1, *buf2;

	buf1 = malloc2(5); /* "hello" */
	buf2 = malloc2(5); /* "world" */

	memcpy(buf1, "hello", 5);
	memcpy(buf2, "world", 5);

	printf("buf1: %s\n", buf1);
	printf("buf2: %s\n", buf2);

	free2(buf1);
	free2(buf2);

	/* seg fault, double free */
	printf("buf1: %s\n", buf1);

	return 0;
}

