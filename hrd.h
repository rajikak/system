#ifndef HRD_H
#define HRD_H

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>


typedef enum {FALSE, TRUE} bool;

#define min(m,n) ((m) < (n)? (m):(n))
#define max(m,n) ((m) > (n)? (m):(n))

#endif
