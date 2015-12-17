#include "randlib.h"
#include <immintrin.h>

// contain the hardware implementation of the random number generator

/* Initialize the hardware rand64 implementation.  */
__attribute__ ((constructor)) void
hardware_rand64_init (void)
{
}

/* Return a random value, using hardware operations.  */
extern unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

/* Finalize the hardware rand64 implementation.  */
__attribute__ ((destructor)) void
hardware_rand64_fini (void)
{
}
