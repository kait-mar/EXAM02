#include "ft_printf.h"
#include <stdio.h>
int main()
{
  int i;
  i = 0;
  char *s = NULL;
   // printf("hello world %s, yes %5.5x %s\n", s, -5485846, s);
    ft_printf("hello world, yes %15.9x %d\n", 51684, 3);
    printf("hello world, yes %15.9x %d\n", 51684, 3);
    
  // printf("|%5.3d|\n", 6);
  //precision avec s et x
  //while (1)
  //  i++;
  return (0);
}
