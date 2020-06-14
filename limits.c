/* system limits - gcc -Wall -ansi -pedantic */

#include "hdr.h"

int main(){
	long lim;

	lim = sysconf(_SC_MQ_PRIO_MAX);
	if(lim == -1) {
		fprintf(stderr, "sysconf error, errno=%d\n", errno);
	} else {
		printf("message queue priorities:%ld\n", sysconf(_SC_MQ_PRIO_MAX));
	}

	printf("min path name len:%ld\n", pathconf("/var/log/", _PC_NAME_MAX));
	printf("min file desc:%ld\n", sysconf(_SC_OPEN_MAX));
	printf("min page size:%ld\n", sysconf(_SC_PAGESIZE));
	printf("distant signal:%ld\n", sysconf(_SC_RTSIG_MAX));
}
