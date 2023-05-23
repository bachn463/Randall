#include "mrand.h"
#include <stdlib.h>

void mrand48_init(char* filepath) {}

unsigned long long mrand48_rng(void) {
  struct drand48_data buf = {0};
  srand48_r(69, &buf);
  long int a, b;
  mrand48_r(&buf, &a);
  mrand48_r(&buf, &b);
  return (((unsigned long long) a) << 32) | ((unsigned long long) b & 0x00000000FFFFFFFF);
}

void mrand48_fini(void) {}
