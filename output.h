#include <stdbool.h>

#ifndef OPTIONS
#define OPTIONS

bool writebytes(unsigned long long x, int nbytes);
int tostdout(long long nbytes, unsigned long long (* rand64) (void));
int writeToN(long long nbytes, unsigned long long (* rand64) (void), long length);

#endif 
