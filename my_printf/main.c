#include "ft_printf.h"
#include <stdio.h>
int main()
{
    char *s;
    s = "hi";
    //printf("hello world %d, yes %x %s\n", -0, 5485846, s);
   // ft_printf("hello world %d, yes %x %s\n", -0, 5485846, s);
   printf("|%5.3d|\n", 6);
}