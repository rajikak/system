#include "hdr.h"

int main(){
	
	time_t t;
	clock_t c;
	struct tms st;
	long clock_ticks = 0;

	t = time(NULL);

	printf("epoch=%ld\n", (long)t);
	printf("time=%s", ctime(&t));

	/* cpu time */
	c = times(&st);
	if (c == -1) {
		fprintf(stderr, "times error: errno=%d\n", errno);
		return -1;
	}

    clock_ticks = sysconf(_SC_CLK_TCK);
	printf("clock_ticks=%ld, cpu=%.4f, system=%.4f\n", clock_ticks, (double) st.tms_utime / clock_ticks, (double) st.tms_stime / clock_ticks);

	return 0;
}
