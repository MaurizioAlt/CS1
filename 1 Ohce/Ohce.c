// Maurizio Altamura
//4232977

#include "Ohce.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

  int i = 1, j=0, flag=0;

  if(argc == 1)
    return 0;

  while(i < argc)
  {
    j = strlen(argv[i]);

    while(j != 0)
    {
      --j;
      printf("%c", argv[i][j]);
    }

    i++;

    if(i != argc)
      printf(" ");
  }

  printf("\n");

  for (i = 1; i < argc; i++)
  {
    j = strlen(argv[i]);

    while(j != 0)
    {
      --j;
      if(argv[i][j] == 'o' || argv[i][j] == 'O')
        if(argv[i][j-1] == 'h' || argv[i][j-1] == 'H')
          if(argv[i][j-2] == 'c' || argv[i][j-2] == 'C')
            if(argv[i][j-3] == 'e' || argv[i][j-3] == 'E')
            {
              printf("Echo, echo, echo!\n");
              flag = 1;
              break;
            }
      if(flag == 1)
      break;
    }

  }

  return 0;
}

double difficultyRating(void)
{
  return 4.9;
}

double hoursSpent(void)
{
  return 12.0;
}
