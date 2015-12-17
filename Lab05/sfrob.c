#include <stdio.h>
#include <stdlib.h>

int xor42cmp(char a, char b)
{
  return (a ^ 0b00101010) - (b ^ 0b00101010);
}

int frobcmp (char const * a, char const * b)
{
  int size_a = 0;
  int size_b = 0;
  int i = 0;
  const char *ap = *(const char **)a;
  const char *bp = *(const char **)b;
  while (ap[size_a] != ' ')
    {
      size_a++;
    }
  while(bp[size_b] != ' ')
    {
      size_b++;
    }
  while(1)
    {
      if (size_a == size_b && i >= size_a)
	return 0;
      if ( i >= size_a )
	return -1;
      if ( i >= size_b )
	return 1;
      int result = xor42cmp(ap[i],bp[i]);
      if (result == 0)
	  i++;
      else
	  return result;
    }
}

// frobcmp wrapper
int Wfrobcmp(const void * a, const void * b)
{
  return frobcmp((char const *)a,(char const *)b);
}

int main()
{
  int bsize = 5096;
  char *input = (char*) malloc(sizeof(char) * bsize);
  if (input == NULL)
    {
      fprintf(stderr, "ERROR - Could not allocate dynamic memory");
      exit(1);
    }
  
  char c;
  int pos = 0;
  int empty = 1;		       
  // Read in all the input from stdin
  while(1)
    {
      // Check for error in reading input
      c = getchar();
      if (c == EOF)
	{
	  if (ferror(stdin))
	    {
	      fprintf(stderr, "ERROR - Could not read from input");
	      exit(1);
	    }
	  break;
	}
      empty = 0;
      input[pos] = (char) c;
      pos++;
      if (pos == bsize)
	{
	  bsize *= 2; // Inrease size of buffer
	  input = (char*) realloc(input, bsize);
	  if (input == NULL)
	    {
	      fprintf(stderr, "ERROR - Could not allocate dynamic memory");
	      exit(1);
	    }
	}
    }

  if (empty == 1)
      return 0;

  // Create ending space in case it isn't there
  if (input[pos-1] != ' ')
    input[pos++] = ' ';
  
  // Create arrays of pointers to the seperate segments
  int spaces = 0;
  for (int k = 0; k < pos; k++)
    {
      if ( input[k] == ' ' )
	spaces++;
    }

  char **tempArray = (char**) malloc(sizeof(char*) * spaces);
  int *lengthArray = (int*) malloc(sizeof(int) * spaces);
  if (tempArray == NULL | lengthArray == NULL)
    {
      fprintf(stderr, "ERROR - Could not allocate dynamic memory");
      exit(1);
    }
  int tempIndex = 0;
  char *tempPointer = input;

  for (int j = 0; j < spaces; j++)
    {
      if (j == 0 && *tempPointer == ' ')
	{
	  tempArray[tempIndex] = tempPointer;
	  tempIndex++;
	  j++;
	  tempPointer++;
	}
      tempArray[tempIndex] = tempPointer;
      tempIndex++;
      while (*tempPointer != ' ')
	tempPointer++;
      tempPointer++;
    }

  qsort(tempArray, tempIndex, sizeof(char*), Wfrobcmp);

  int length = 1;
  int lengthIndex = 0;
  for (int h = 0; h < spaces; h++)
    {
      tempPointer = tempArray[h];
      while (*tempPointer != ' ')
	{
	  tempPointer++;
	  length++;
	}
      lengthArray[lengthIndex] = length;
      lengthIndex++;
      length = 1;
    }
  for (int l = 0; l < spaces; l++)
    {
      char * toPrint = tempArray[l];
      for (int i = 0; i < lengthArray[l]; i++)
	{
	  // Check for error during output
	  if (putchar(*toPrint) == EOF)
	    {
	      fprintf(stderr, "ERROR - Could not output correctly");
	      exit(1);
	    }
	  toPrint++;
	}
    }
  free(input);
  free(tempArray);
  free(lengthArray);
  return 0;
}
