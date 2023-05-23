#include <stdbool.h>

#ifndef OUTPUT
#define OUTPUT

bool writebytes(unsigned long long x, int nbytes);
int tostdout(long long nbytes, unsigned long long (* rand64) (void));
int writeWithN(long long nbytes, unsigned long long (* rand64) (void), long length);

#endif 
