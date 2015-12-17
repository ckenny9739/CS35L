#include <stdio.h>
#include <string.h>

int mem(int i)
{
  return i ^ 42;
}

int main()
{
  int * c;
  printf("tr \'");
  for (int i = 0; i < 256; i++)
    {
      c[i] = i;
      printf("\\%03o", c[i]);
    }
  printf("\' \'");
  for (int i = 0; i < 256; i++)
    {
      int next = mem(c[i]);
      printf("\\%03o", next);
    }  
  printf("\'\nsort |\ntr \'");
}
