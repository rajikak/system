/*./brk num size step max min*/
#include "hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]) {

	char *ptr[MAX_ALLOCS];
	int j, step, min, max, size, num;

	num  = atoi(argv[1]);
	size = atoi(argv[2]);
	step = atoi(argv[3]);
	min  = atoi(argv[4]);
	max  = atoi(argv[5]);

	printf("initial program break: %10p\n", sbrk(0));
	printf("allocating %d*%d bytes\n", num, size);

	for(j = 0; j < num; j++) {
		ptr[j] = malloc(size);
		if(ptr[j] == NULL) {
			fprintf(stderr, "malloc error, errno=%d\n", errno);
			return -1;
		}
	}

	printf("program break now:%10p\n", sbrk(0));
	printf("freeing blocks from %d to %d in steps of %d\n", min, max, step);

	for(j = min - 1; j < max; j += step) {
		free(ptr[j]);
	}

	printf("after free(), program break is: %10p\n", sbrk(0));
	return 0;
}
