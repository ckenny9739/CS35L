// tr2u.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[])
{
  if (argc != 3)
    {
      fprintf (stderr, "Error - need 2 operands\n");
      exit(1);
    }
  char * from = argv[1];
  char * to = argv[2];
  if (from == NULL || to == NULL)
    {
      fprintf (stderr, "Error - cannot be emtpy\n");
      exit(1);
    }
  int sizeF = 0;
  int sizeT = 0;
  int k = 0;
  while (from[k] != '\0')
    {
      sizeF += 1;
      k += 1;
    }
  k = 0;
  while(to[k] != '\0')
    {
      sizeT += 1;
      k += 1;
    }
  if (sizeF != sizeT)
    {
      fprintf (stderr, "Error - froma and to are different sizes\n");
      exit(1);
    }
  int max, i, j;
  for (i = 0; i < sizeF; i++)
    for (j = 0; j < sizeF; j++)
      if (i != j && from[i] == from [j])
	{
	  fprintf (stderr, "Error - from has duplicates\n");
	  exit(1);
	}
  int ch, printed;
  while (read(0, &ch, 1) > 0)
    {
      printed = 0;
      for (i = 0; i < sizeF; i++)
	{
	  if (ch == from[i])
	    {
	      write(1, to + i, 1);
	      printed = 1;
	      break;
	    }
	}
      if (printed == 0)
	write(1, &ch, 1);
    }  
  return 0;     
}
