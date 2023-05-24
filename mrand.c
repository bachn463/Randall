#include "mrand.h"
#include <stdlib.h>
#include <time.h>

void mrand48_init(char* filepath) {}

unsigned long long mrand48_rng(void) {
  struct drand48_data randbuffer;
  long int seed = time(NULL);
  srand48_r(seed, &randbuffer);
  //  fprintf(stderr, "%li\n", seed);
  
  // mrand creates a 32 bit, but we need a 64 bit 
  long int upper, lower;
  mrand48_r(&randbuffer, &upper);
  mrand48_r(&randbuffer, &lower);

  // fprintf(stderr, "rands: %x, %x\n", (unsigned int)upper, (unsigned int)lower);
  
  return (((unsigned long long) upper) << 32) | ((unsigned long long) lower);
}

void mrand48_fini(void) {}
