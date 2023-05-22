#ifndef RAND64HW
#define RAND64HW

void hardware_rand64_init (char* str);
unsigned long long hardware_rand64 (void);
void hardware_rand64_fini (void);

#endif
