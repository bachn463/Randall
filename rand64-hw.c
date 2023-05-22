#include <rand64-hw.h>

/* Initialize the hardware rand64 implementation.  */
void
hardware_rand64_init (char* filepath)
{
}

/* Return a random value, using hardware operations.  */
unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;

  /* Work around GCC bug 107565
     <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=107565>.  */
  x = 0;

  while (! _rdrand64_step (&x))
    continue;
  return x;
}

/* Finalize the hardware rand64 implementation.  */
void
hardware_rand64_fini (void)
{
}
