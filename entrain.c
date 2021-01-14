#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_counter;
int i;
int j;
char	specifier;

void	ft_putchar(char c);
void	ft_putnbr2(long nbr);
void	ft_putstr(char *s);
void	ft_putnbr(long nbr);
int		ft_strlen(char *s);
int		ft_atoi(char *s);
int		ft_len(long nbr);
int		find(char *s, char c);
int		is_format(char c);
void	print_format(char *format, va_list list);
int		len_hexa(unsigned int n);
void	print_prec(char **format, va_list list);
void	get_prec(char **format);
void	print_space(int k);
void	sub_putstr(char *str, int j);
void	string_handler(char *s);
int		int_len(long nbr);
void	int_handler(int n);
void	print_zero(int k);
void	dec_to_hexa(unsigned int n);
void	other_handler(char c);
void	print_width(char **format, va_list list);

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

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putnbr(long nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 0 && nbr <= 9)
		ft_putchar(nbr + '0');
	else
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
		nbr /= 10;
	}
}

void	ft_putnbr2(long nbr)
{
	if (nbr < 0)
	{
		nbr = -nbr;
	}
	if (nbr >= 0 && nbr <= 9)
		ft_putchar(nbr + '0');
	else
	{
		while (nbr != 0)
		{
			ft_putnbr(nbr / 10);
			ft_putchar(nbr % 10 + '0');
			nbr /= 10;
		}
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

int		ft_len(long nbr)
{
	if (nbr < 0)
		return (1);
	return (0);
}

int		int_len(long nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
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

int		is_format(char c)
{
	return (c == 'x' || c == 'd' || c == 's');
}

void	print_format(char *format, va_list list)
{
	char	*s;

	if (*format == 's')
	{
		s = va_arg(list, char *);
		if (s == NULL)
			s = "(null)";
		ft_putstr(s);
	}
	else if (*format == 'd')
		ft_putnbr(va_arg(list, int));
	else if (*format == 'x')
	{
		dec_to_hexa(va_arg(list, unsigned int));
	}
}

int		len_hexa(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 0 && n <= 16)
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

void	dec_to_hexa(unsigned int n)
{
	char	reverse[len_hexa(n)];
	int		i;

	i = 0;
	while (n != 0)
	{
		reverse[i++] = num_char(n % 16);
		n /= 16;
	}
	while (i >= 0)
	{
		ft_putchar(reverse[i--]);
	}
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	get_prec(char **format)
{
	char	*width;

	i = 0;
	while ((*format)[i] && ft_isdigit((*format)[i]))
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
	while ((*format)[j] && ft_isdigit((*format)[j]))
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

void	sub_putstr(char *str, int j)
{
	while (--j >= 0)
	{
		ft_putchar(*str);
		str++;
	}
}

void	string_handler(char *s)
{
	char	*str;
	int		l;
	int		k;

	str = s;
	if (s == 0)
		str = "(null)";
	l = ft_strlen(str);
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
		ft_putstr(str);
	else
		sub_putstr(str, j);
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
		if (j < l)
			print_space(i - l - ft_len(n));
		else
			print_space(i - j - ft_len(n));
	}
	if (n < 0)
		ft_putchar('-');
	print_zero(j - int_len(nbr));
	if (!(j == 0 && n == 0))
		ft_putnbr(nbr);
}

void	hexa_handler(unsigned int n)
{
	int		l;
	char	*s;
	l = len_hexa(n);
	if (j == 0 && n == 0)
		print_space(i);
	else if (i > j)
	{
		if (j < l)
			print_space(i - l);
		else
			print_space(i - j);
	}
	print_zero(j - len_hexa(n));
	if (!(j == 0 && n == 0))
		dec_to_hexa(n);
}

void	other_handler(char c)
{
	print_space(i - 1);
	ft_putchar(c);
}

void	print_prec(char **format, va_list list)
{
	get_prec(format);
	if (**format == 's')
		string_handler(va_arg(list, char *));
	else if (**format == 'd')
		int_handler(va_arg(list, int));
	else if (**format == 'x')
		hexa_handler(va_arg(list, unsigned int));
	else
		other_handler(**format);
}

int		ft_printf(char *format, ...)
{
	va_list	list;

	va_start(list, format);
	i = 0;
	j = 0;
	while (*format != '\0')
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			format++;
			if (find(format, '.'))
				print_prec(&format, list);
			else if (ft_isdigit(*format))
				print_width(&format, list);
			else if (is_format(*format))
				print_format(format, list);
			else
				ft_putchar(*format);
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(list);
	return (g_counter);
}

void	print_width(char **format, va_list list)
{
	long	d;
	char	*s;
	unsigned int	x;

	get_prec(format);
	if (**format == 's')
	{
		s = va_arg(list, char *);
		print_space(i - ft_strlen(s));
		ft_putstr(s);
	}
	else if (**format == 'd')
	{
		d = va_arg(list, int);
		print_space(i - int_len(d) - ft_len(d));
		ft_putnbr(d);
	}
	else if (**format == 'x')
	{
		print_space(i - len_hexa(x));
		dec_to_hexa(x);
	}
	else
	{
		print_space(i - 1);
		ft_putchar(**format);
	}
}