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
            const_struct(&structure, list, format);
            print(structure, format);
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
        x = (unsigned int)va_arg(list, unsigned int);
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

void    print_format(t_list *structure, const char *format)
{
	if (*format == 's')
		ft_putstr(structure->s);
	else if (*format == 'd')
		ft_putnbr(structure->d);
	else if (*format == 'x')
		ft_putstr(dec_to_hex(structure->x));
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*(str++));
}

void	ft_putnbr(int n)
{
	int		tab[100];
	int		i;

	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	i = 0;
	while (n != 0)
	{
		tab[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i-- > 0)
		ft_putchar(tab[i]);
}

char	*dec_to_hex(unsigned int n)
{
	char	reverse[lenght(n)];
	char	converted[lenght(n)];
	int		i;
	int		nb;

	if (n == 0)
	{
		converted[0] = '0';
		converted[1] = '\0';
	}
	else
	{
		i = 0;
		while (n != 0)
		{
			reverse[i++] = char_num(n % 16);
			n /= 16;
		}
		while (--i >= 0)
			converted[nb++] = reverse[i];
		converted[nb] = '\0';
	}
	return (converted);
}