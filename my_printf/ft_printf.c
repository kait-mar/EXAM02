#include "ft_printf.h"

int     ft_printf(const char *format, ...)
{
    va_list list;
    t_list  *structure;
    int     integer1;
    int     integer2;

    g_counter = 0;
    va_start(list, format);
    while (*format)
    {
        if (*format == '%' && *format != '%')
        {
            format++;
            structure = malloc(sizeof(t_list));
            const_flag(list, &format, &integer1, &integer2);
            const_struct(&structure);
            

        }
        else
        {
            while (*format != '%')
                ft_putchar(*(format++));
        }
        
    }
    return (g_counter);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    const_struct(t_list *structure, va_list list, const char *format)
{
    int i;
    char    *s;
    int     d;
    unsigned int    x;

    i = 0;
    while (format[i] && is_format(format[i]) == 0)
        i++;
    if (format[i] == 's')
    {
        s = (char *)va_arg(list, char *);
        if (s == NULL)
            s = "(null)";
        structure->s = s;
    }
    else if (format[i] == 'd')
    {
        d = (int)va_arg(list, int);
        structure->d = d;
    }
    else if (format[i] == 'x')
    {
        x = (unsigned int)va_argv(list, unsigned int);
        structure->x = x;
    }
}

int     is_format(char c)
{
    if (c == 'd' || c == 'x' || c == 's')
        return (1);
    else
        return (0);
}
void    const_flag(va_list list, const char *format, int *integer1, int *integer2)
{
    char *str;

    while ()
}