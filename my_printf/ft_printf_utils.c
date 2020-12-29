#include "ft_printf.h"

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

void    ft_putchar(char c)
{
    write(1, &c, 1);
	g_counter++;
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

char	*dec_to_hexa(unsigned long long n)
{
	char	reverse[unsign_lenght(n)];
	char	*converted;
	int		i;
	int		nb;

	converted = malloc(unsign_lenght(n) + 1);
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
		nb = 0;
		while (--i >= 0)
			converted[nb++] = reverse[i];
		converted[nb] = '\0';
	}
	return (converted);
}

char    char_num(int n)
{
    if (n >= 0 && n <= 9)
        return (n + '0');
    else
    	return (n + 87);
}

int		unsign_lenght(unsigned long long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int		lenght(int n)
{
	int	i;

	i = 0;
	if (i == 0)
		return (1);
	if (i < 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int     is_format(char c)
{
    if (c == 'd' || c == 'x' || c == 's')
        return (1);
    else
        return (0);
}

int     find(char *str, char c)
{
    while (*str && *str != '%')
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}

int     ft_atoi(char *num)
{
    int 	i;
    long		n;
	int			s;

    i = 0;
    n = 0;
	s = 1;
	if (*num == '-')
	{
		s = -1;
		num++;
	}
    while (num[i])
    {
        n = n + ((num[i] - '0') * 10);
        i++;
    }
    return (s * n);
}
