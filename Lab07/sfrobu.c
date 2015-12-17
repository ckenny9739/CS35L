#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int numCompares = 0;

int xor42cmp(char a, char b)
{
  return (a ^ 0b00101010) - (b ^ 0b00101010);
}

int frobcmp (char const * a, char const * b)
{
  numCompares++;
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
  struct stat s;
  fstat(0, &s);
  int fsize = s.st_size;
  int c;
  int bsize = 4096;
  int count = 0;
  char* input;


  // Regular file section is wrong
  // If it takes it in as a file, the multiple character ones get split


  
  // If it is a regular file
  if (S_ISREG(s.st_mode))
    {
      fprintf(stderr, "REGULAR FILE\n\n\n\n");
      // Check for empty (don't waste time allocating)
      if (read(0, &c, 1) == 0)
	{
	  fprintf(stderr, "Comparisons: %d\n", numCompares);
	  return 0;
	}
      input = (char*) malloc(sizeof(char)* fsize);
      if (input == NULL)
	{
	  fprintf(stderr, "ERROR - Could not allocate dynamic memory");
	  exit(1);
	}
      int cursize = fsize;
      int k = 0;
      input[count++] = c;
      while (k < fsize)
	{
	  if (read(0, &c, 1) == -1)
	    {
	      fprintf(stderr, "ERROR - Could not read correctly");
	      exit(1);
	    }
	  input[count++] = c;
	  if (count == cursize)
	    {
	      cursize *= 2; // Inrease size of buffer
	      input = (char*) realloc(input, cursize);
	      if (input == NULL)
		{
		  fprintf(stderr, "ERROR - Could not allocate dynamic memory");
		  exit(1);
		}
	    }
	  fstat(0, &s);
	  fsize = s.st_size;
	  k++;
	}
    }
  // Not regular file
  else
    {
      // Check for empty (don't wast time allocating)
      if (read(0, &c, 1) == 0)
	{
	  fprintf(stderr, "Comparisons: %d\n", numCompares);
	  return 0;
	}
      input = (char*) malloc(sizeof(char)* bsize);
      if (input == NULL)
	{
	  fprintf(stderr, "ERROR - Could not allocate dynamic memory");
	  exit(1);
	}
      input[count++] = c;
      while (read(0, &c, 1) > 0)
	{
	  input[count++] = c;
	  if (count == bsize)
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
    }
  // Create ending space in case it isn't there
  if (input[count-1] != ' ')
    input[count++] = ' ';
  
  // Create arrays of pointers to the seperate segments
  int spaces = 0;
  for (int k = 0; k < count; k++)
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
      char* toPrint = tempArray[l];
      for (int i = 0; i < lengthArray[l]; i++)
	{
	  // Check for error during output
	  if (write(1, &(*toPrint), 1) == -1)
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
  fprintf(stderr, "Comparisons: %d\n", numCompares);
  return 0;
}
