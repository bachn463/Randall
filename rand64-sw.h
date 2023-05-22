#ifndef RAND64SW
#define RAND64SW

void software_rand64_init (char* filepath);
unsigned long long software_rand64 (void);
void software_rand64_fini (void);

#endif
