#include "ft_printf.h"
#include <stdio.h>

int     ft_printf(const char *format, ...)
{
    va_list list;
    t_list  *structure;

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
	free(structure);
    return (g_counter);
}

void	print(t_list *structure, const char **format)
{
	int	i;
	i = 0;
	if (ft_isdigit(**format) || find(*format, '.'))
		print_prec(structure, format);
	else if (is_format(**format))
		print_format(structure, *format);
	(*format)++;
}

void	print_prec(t_list *structure, const char **format)
{
	char	*width;
	int		i;
	int		j;
	int		k;

	j = 0;
	i = 0;
	while ((*format)[i] && ft_isdigit((*format)[i]))
		i++;
	width = malloc(i + 1);
	while (**format && ft_isdigit(**format))
		width[j++] = *(*format)++;
	width[j] = '\0';
	//add a free for width here
	j = ft_atoi(width);
	//printf("\n  j == |%d|\n", j);
	free(width);
	if (**format == '.')
		(*format)++;
	i = 0;
	while ((*format)[i] && ft_isdigit((*format)[i]))
	{
		i++;
	}
	width = malloc(i + 1);
	i = 0;
	while (**format && ft_isdigit(**format))
		width[i++] = *(*format)++;
	width[i] = '\0';
	i = ft_atoi(width);
	free(width);
	//printf("\n|i == %d|\n", i);
    if (i == 0 && ((**format == 'd' && structure->d == 0) || (**format == 'x' && structure->x == 0)))
    {
        while (--j >= 0)
		ft_putchar(' ');
    }
    else
    {
        if (i != 0 && **format == 's')
            k = j - ft_lenght(structure, *format);
        else
            k = j - i;
           // k = j - i - ft_lenght3(structure, *format);
        //printf("|%d|\n", k);
         if (**format == 'd' && structure->d < 0)
            k--;
        while (--k >= 0)
            ft_putchar(' ');
        if (**format == 'd' && structure->d < 0)
            ft_putchar('-');
        if (!(i != 0 && **format == 's'))
        {
			//printf("\n|i == %d|\n", ft_lenght(structure, *format));
             k = i - ft_lenght(structure, *format);
            while (--k >= 0)
            	ft_putchar('0');
        }
        print_format2(structure, *format);
    }
}

void    const_struct(t_list *structure, va_list list, const char *format)
{
    int 			i;
    char    		*s;
    int     		d;
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
	char	*s;

	if (*format == 's')
		ft_putstr(structure->s);
	else if (*format == 'd')
		ft_putnbr(structure->d);
	else if (*format == 'x')
	{
		s = dec_to_hexa(structure->x);
		ft_putstr(s);
		free(s);
	}
}

void    print_format2(t_list *structure, const char *format)
{
	char	*s;

	if (*format == 's')
		ft_putstr(structure->s);
	else if (*format == 'd')
		ft_putnbr2(structure->d);
	else if (*format == 'x')
	{
		s = dec_to_hexa(structure->x);
		ft_putstr(s);
		free(s);
	}
}
