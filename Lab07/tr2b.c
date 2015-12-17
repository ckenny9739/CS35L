// tr2b.c
#include <stdio.h>
#include <stdlib.h>

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
      fprintf (stderr, "Error - cannot be empty\n");
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
      fprintf (stderr, "Error - must be the same size\n");
      exit(1);
    }
  int max, i, j;
  for (i = 0; i < sizeF; i++)
    for (j = 0; j < sizeF; j++)
      if (i != j && from[i] == from [j])
	{
	  fprintf (stderr, "Error - from can't have duplicates\n");
	  exit(1);
	}
  int ch, printed;
  while (1)
    {
      ch = getchar();
      if (ch == EOF)
	break;
      printed = 0;
      for (i = 0; i < sizeF; i++)
	{
	  if (ch == from[i])
	    {
	      putchar(to[i]);
	      printed = 1;
	      break;
	    }
	}
      if (printed == 0)
	putchar(ch);
    }
  return 0;     
}
