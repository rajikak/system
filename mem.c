#include <stdio.h>
#include <stdlib.h>

char glob_buf[65536];
int primes[] = {2, 3, 5, 7};

static int square(int x) {

	int result;
	result = x * x;
	return result;
}

static void calc(int val) {

	printf("The square of %d is %d\n", val, square(val));
	if (val < 1000) {
	
		int t;
		t = val * val * val;
		printf("the cube of %d is %d\n", val, t);
	}
}

int main(int argc, char *argv[]) {

	static int key = 9973;
	static char mbuf[10240000];
	char *p;

	p = malloc(1024);
	calc(key);
	
	exit(EXIT_SUCCESS);
}
