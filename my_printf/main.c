#include "ft_printf.h"
#include <stdio.h>
int main()
{
    char *s;
    s = "hi";
    printf("hello world %.6d, yes %x %s\n", 6, 5485846, s);
    ft_printf("hello world %.6d, yes %x %s\n", 6, 5485846, s);
  // printf("|%5.3d|\n", 6);
  return (0);
}
