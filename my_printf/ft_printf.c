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
        if (*format == '%' && *(format + 1) != '%')
        {
            format++;
            structure = malloc(sizeof(t_list));
            const_struct(structure, list, format);
            print(structure, &format);
        }
        else
        {
            while (*format != '\0' && *format != '%')
                ft_putchar(*(format++));
        }
    }
    return (g_counter);
}

void	print(t_list *structure, const char **format)
{
	int	i;
	i = 0;
	if (ft_isdigit(**format))
	{
		print_width(structure, &format);
	}
	else if (is_format(**format))
	{
		print_format(structure, *format);
		(*format)++;
	}
}

void	print_width(t_list *structure, const char **format)
{
	int		i;
	int		j;
	char	*width;

	i = 0;
	j = 0;
	while (ft_isdigit(format[i]))
		i++;
	width = malloc(i + 1);
	i = 0;
	while (ft_isdigit(format[i]))
		width[i++] = *(*format)++;
	width[i] = '\0';
	if (format[i] == 'd')
		j = ft_atoi(width) - lenght(structure->d);
	else if (format[i] == 's')
		j = ft_atoi(width) - ft_strlen(structure->s);
	else if (format[i] == 'x')
		j = ft_atoi(width) - ft_strlen(dec_to_hexa(structure->x));
	while (--j >= 0)
		ft_putchar(' ');
	print_format(structure, format);
	(*format)++;
	free(width);
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
        x = (unsigned int)va_arg(list, unsigned int);
        structure->x = x;
    }
}

void    print_format(t_list *structure, const char *format)
{
	if (*format == 's')
		ft_putstr(structure->s);
	else if (*format == 'd')
		ft_putnbr(structure->d);
	else if (*format == 'x')
		ft_putstr(dec_to_hexa(structure->x));
}
