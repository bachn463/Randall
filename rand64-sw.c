#include "rand64-sw.h"
#include <stdio.h>
#include <stdlib.h>

/* Input stream containing random bytes.  */
FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void software_rand64_init (void)
{
  urandstream = fopen ("/dev/random", "r");
  if (! urandstream) {
    fprintf(stderr, "Invalid filepath: %s\n", filepath);
    exit(1);
  }
}

/* Return a random value, using software operations.  */
unsigned long long software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1) {
    fprintf(stderr, "Could not read file\n");
    exit(1);
  }
  return x;
}

/* Finalize the software rand64 implementation.  */
void software_rand64_fini (void)
{
  fclose (urandstream);
}}
