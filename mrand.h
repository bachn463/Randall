#ifndef MRAND
#define MRAND

void mrand48_init(char* filepath);
unsigned long long mrand48_rng(void);
void mrand48_fini(void);

#endif
