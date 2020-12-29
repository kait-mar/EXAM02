#ifndef FT_PRINTF_H
#define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int g_counter;
typedef struct s_list
{
    int             d;
    char            *s;
    unsigned int    x;
}   t_list;
typedef struct s_flag
{
    int integer1;
    int integer2;
}       t_flag;

void    ft_putchar(char c);

#endif