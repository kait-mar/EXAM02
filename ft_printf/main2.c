#include <stdio.h>

int ft_printf(const char *fmt, ...);

int main()
{
    printf("[%6.10s]\n", "sara");
    ft_printf("[%6.10s]", "sara");
}