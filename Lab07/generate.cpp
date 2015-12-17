#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

/* Program to generate random ASCII characters */

int main()
{
	srand(time(NULL));
		char temp;
		     int n;
		     	 cin >> n;
			     for (int k = 0; k < n; k++)
			     	 {
						temp = (char)(rand() % 254);
						       printf("%c ", temp);
						       		      }
								      }
