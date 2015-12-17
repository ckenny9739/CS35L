#include "randlib.h"
#include <stdlib.h>
#include <stdio.h>


// randlibsw.c should contain the software implementation of the random number generator
// implement the interface described by randlib.h.
// Since the software implementation needs initialization and finalization
// this implementation should also define an initializer and a finalizer function
// using GCC's “__attribute__ ((constructor))” and “__attribute__ ((destructor))” declaration specifiers.

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
__attribute__ ((constructor)) void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
extern unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
__attribute__ ((destructor)) void
software_rand64_fini (void)
{
  fclose (urandstream);
}
