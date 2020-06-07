/* process credentials */

#define _GNU_SOURCE
#include "hdr.h"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(){

	uid_t ruid, euid, suid, fsuid;
	gid_t rgid, egid, sgid, fsgid;
	gid_t support_groups[SG_SIZE];
	int num_groups, j;
	char *p;
	

	if(getresuid(&ruid, &euid, &suid) == -1){
		fprintf(stderr, "getresuid failed: errno: %d\n", errno);
		return -1;
	}
	if(getresgid(&rgid, &egid, &sgid) == -1) {
		fprintf(stderr, "getresgid failed: errno: %d\n", errno);
		return -1;
	}

	fsuid = setfsuid(0);
	fsgid = setfsgid(0);

	printf("uid-real=%ld, effective=%ld, saved=%ld, fs=%ld\n", (long)ruid, (long)euid, (long)suid, (long)fsuid);

	printf("gid-real=%ld, effective=%ld, saved=%ld, fs=%ld\n", (long)rgid, (long)egid, (long)sgid, (long)fsgid);

	return 0;
}

