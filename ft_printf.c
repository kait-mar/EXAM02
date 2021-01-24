#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int		g_counter;
int		i;
int		j;

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(long nbr);
int		ft_atoi(char *s);
void	sub_putstr(char *s, int j);
int		is_format(char c);
int		ft_isdigit(char c);
int		find(char *s, char c);
void	print_format(char *format, va_list list);
void	dec_to_hexa(unsigned int x);
int		hexa_len(unsigned int n);
char	num_char(int n);
void	print_prec(char **format, va_list list);
void	get_width(char **format);
void	string_handler(char *s);
int		ft_strlen(char *s);
void	print_space(int k);
void	print_zero(int k);
int		int_len(long nbr);
int		len(int n);
void	int_handler(int n);
void	hexa_handler(unsigned int n);

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_counter++;
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		ft_putchar(*s);
		s++;
	}
}

void	ft_putnbr(long nbr)
{
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar('-');
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar(nbr + '0');
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
		nbr /= 10;
	}
}

int		ft_atoi(char *s)
{
	int	res;

	res = 0;
	while (*s)
	{
		res = (res * 10) + (*s - '0');
		s++;
	}
	return (res);
}

void	sub_putstr(char *s, int j)
{
	while (--j >= 0 && *s)
	{
		ft_putchar(*s);
		s++;
	}
}

int		is_format(char c)
{
	return (c == 'd' || c == 's' || c == 'x');
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int		find(char *s, char c)
{
	while (*s && *s != '%')
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int		hexa_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 16;
	}
	return (i);
}

char	num_char(int n)
{
	if (n >= 0 && n <= 9)
		return (n + '0');
	return (n + 87);
}

void	dec_to_hexa(unsigned int x)
{
	char	reverse[hexa_len(x)];
	int		i;

	i = 0;
	if (x <= 9)
	{
		ft_putchar(x + '0');
		return ;
	}
	while (x != 0)
	{
		reverse[i++] = num_char(x % 16);
		x /= 16;
	}
	while (--i >= 0)
		ft_putchar(reverse[i]);
}

void	print_format(char *format, va_list list)
{
	char	*s;

	if (*format == 'd')
		ft_putnbr(va_arg(list, int));
	else if (*format == 's')
	{
		s = va_arg(list, char *);
		if (s == NULL)
			s = "(null)";
		ft_putstr(s);
	}
	else if (*format == 'x')
		dec_to_hexa(va_arg(list, unsigned int));
}

void	get_width(char **format)
{
	char	*width;

	i = 0;
	while ((*format)[i] != '\0' && ft_isdigit((*format)[i]))
		i++;
	width = malloc(i + 1);
	i = 0;
	while (**format && ft_isdigit(**format))
	{
		width[i++] = **format;
		(*format)++;
	}
	width[i] = '\0';
	i = ft_atoi(width);
	free(width);
	if (**format == '.')
		(*format)++;
	j = 0;
	while ((*format)[j] != '\0' && ft_isdigit((*format)[j]))
		j++;
	width = malloc(j + 1);
	j = 0;
	while (**format && ft_isdigit(**format))
	{
		width[j++] = **format;
		(*format)++;
	}
	width[j] = '\0';
	j = ft_atoi(width);
	free(width);
}

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	print_space(int k)
{
	while (--k >= 0)
		ft_putchar(' ');
}

void	print_zero(int k)
{
	while (--k >= 0)
		ft_putchar('0');
}

void	string_handler(char *s)
{
	int	l;

	l = ft_strlen(s);
	if (i >= j)
	{
		if (j >= l)
			print_space(i - l);
		else
			print_space(i - j);
	}
	else
	{
		if (j > l)
			print_space(i - l);
	}
	if (j >= l)
		ft_putstr(s);
	else
	sub_putstr(s, j);
}

int		int_len(long nbr)
{
	int	i;

	i = 0;
	if 	(nbr < 0)
		nbr = -nbr;
	if (nbr >= 0 && nbr <= 9)
		return (1);
	while (nbr != 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int		len(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

void	int_handler(int n)
{
	long	nbr;
	int		l;

	nbr = n;
	if (nbr < 0)
		nbr = -nbr;
	l = int_len(nbr);
	if (j == 0 && n == 0)
		print_space(i);
	else if (i > j)
	{
		//this
		if (j > l)
			print_space(i - j - len(n));
		else
			print_space(i - l - len(n));
	}
	if (n < 0)
		ft_putchar('-');
	print_zero(j - l);
	if (!(n == 0 && j == 0))
		ft_putnbr(nbr);
}

void	hexa_handler(unsigned int n)
{
	int		l;

	l = hexa_len(n);
	if (j == 0 && n == 0)
		print_space(i);
	else if (i > j)
	{
		//this
		if (j > l)
			print_space(i - j);
		else
			print_space(i - l);
	}
	print_zero(j - l);
	if (!(n == 0 && j == 0))
		dec_to_hexa(n);
}

void	print_prec(char **format, va_list list)
{
	char	*s;

	get_width(format);
	if (**format == 's')
	{
		s = va_arg(list, char *);
		if (s == NULL)
			s = "(null)";
		string_handler(s);
	}
	else if (**format == 'd')
		int_handler(va_arg(list, int));
	else if (**format == 'x')
		hexa_handler(va_arg(list, unsigned int));
	else
	{
		print_space(i - 1);
		ft_putchar(**format);
	}
}

void	print_width(char **format, va_list list)
{
	char	*s;
	int		d;
	unsigned int	x;

	get_width(format);
	if (**format == 's')
	{
		s = va_arg(list, char *);
		if (s == NULL)
			s = "(null)";
		print_space(i - ft_strlen(s));
		ft_putstr(s);
	}
	else if (**format == 'd')
	{
		d = va_arg(list, int);
		print_space(i - int_len(d) - len(d));
		ft_putnbr(d);
	}
	else if (**format == 'x')
	{
		x = va_arg(list, unsigned int);
		print_space(i - hexa_len(x));
		dec_to_hexa(x);
	}
	else
	{
		print_space(i - 1);
		ft_putchar(**format);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	list;

	va_start(list, format);
	g_counter = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			format++;
			if (is_format(*format))
				print_format((char *)format, list);
			else if (find((char *)format, '.'))
				print_prec((char **)&format, list);
			else if (ft_isdigit(*format))
				print_width((char **)&format, list);
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(list);
	return (g_counter);
}