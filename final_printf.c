#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
int	g_count;
typedef struct s_list{
	int		d;
	char	*s;
	unsigned int	x;
}			t_list;
void	ft_putchar(char c);
void	ft_putstr(char *s);
int		int_len(long nbr);
int		ft_strlen(char *s);
char	num_char(int n);
int		is_format(char c);
int		len_hexa(unsigned int n);
int		ft_atoi(char *s);
void	ft_putnbr(long n);
int		ft_printf(const char *fromat, ...);
void	const_struct(t_list *str, const char *format, va_list list);
int		ft_isdigit(char c);
void	print_format(t_list *str, const char *format);
void	print_prec(t_list *str, const char **format);
int		len(t_list *str, const char *format);
int		find(char *s, char c);
int		ft_len(t_list *str, const char *format);
void	print_format2(t_list *str, const char *format, int j, int yes);
char	*dec_to_hexa(unsigned int n);
void	print(t_list *str, const char **format);

void	ft_putchar(char c)
{
	write(1, &c, 1);
	g_count++;
}

void	ft_putstr(char *s)
{
	int	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

int		int_len(long nbr)
{
	int	i;

	i = 0;
	if (nbr >= 0 && nbr <= 9)
		return (1);
	if (nbr < 0)
		nbr = -nbr;
	while (nbr != 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int		ft_len(t_list *str, const char *format)
{
	while (is_format(*format) == 0)
		format++;
	if (*format == 'd')
		return (int_len(str->d));
	if (*format == 's')
		return (ft_strlen(str->s));
	if (*format == 'x')
		return (len_hexa(str->x));
	return (0);
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

char	num_char(int n)
{
	if (n >= 0 && n < 10)
		return (n + '0');
	return (n + 87);
}

int		ft_atoi(char *s)
{
	int	n;
	n = 0;
	while (*s)
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n);
}

int		len_hexa(unsigned int n)
{
	int	i;

	i = 0;
	if (n >= 0 && n <= 9)
		return (1);
	while (n != 0)
	{
		i++;
		n /= 16;
	}
	return (i);
}

int		is_format(char c)
{
	return (c == 'd' || c == 's' || c == 'x');
}

void	ft_putnbr(long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
		n = n / 10;
	}
	else
	{
		ft_putchar(n + '0');
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	list;
	t_list	*str;

	va_start(list, format);
	str = malloc(sizeof(t_list));
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			format++;
			const_struct(str, format, list);
			print(str, &format);
		}
		else
		{
			ft_putchar(*format);
			format++;
		}
	}
	free(str);
	va_end(list);
	return (g_count);
}

void	const_struct(t_list *str, const char *format, va_list list)
{
	int	i;
	char	*s;

	i = 0;
	while (is_format(format[i]) == 0)
		i++;
	if (format[i] == 'd')
		str->d = va_arg(list, int);
	else if (format[i] == 's')
	{
		s = va_arg(list, char *);
		if (s == 0)
			s = "(null)";
		str->s = s;
	}
	else if (format[i] == 'x')
		str->x = va_arg(list, unsigned int);
}

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	print(t_list *str, const char **format)
{
	if (ft_isdigit(**format) || find((char *)*format, '.'))
		print_prec(str, format);
	else if (is_format(**format))
		print_format(str, *format);
	(*format)++;
}

void	print_format(t_list *str, const char *format)
{
	char	*s;

	if (*format == 'd')
	{
		//printf("what enters here %d\n", str->d);
		ft_putnbr(str->d);
	}
	else if (*format == 's')
		ft_putstr(str->s);
	else if (*format == 'x')
	{
		s = dec_to_hexa(str->x);
		ft_putstr(s);
		free(s);
	}
}

void	print_prec(t_list *str, const char **format)
{
	char	*width;
	int		i;
	int		j;
	int		k;
	int		yes;

	i = 0;
	yes = 0;
	while ((*format)[i] && ft_isdigit((*format)[i]))
		i++;
	width = malloc(i + 1);
	i = 0;
	while (ft_isdigit(**format))
	{
		width[i++] = **format;
		(*format)++;
	}
	width[i] = '\0';
	i = ft_atoi(width);
	free(width);
	if (**format == '.')
	{
		yes = 1;
		(*format)++;
	}
	j = 0;
	while (ft_isdigit((*format)[j]))
		j++;
	width = malloc(j + 1);
	j = 0;
	while (ft_isdigit(**format))
	{
		width[j++] = **format;
		(*format)++;
	}
	width[j] = '\0';
	j = ft_atoi(width);
	free(width);
	if (yes == 1 && j == 0 && ((**format == 'd' && str->d == 0) || (**format == 'x' && str->x == 0)))
	{
		while (--i >= 0)
			ft_putchar(' ');
	}
	else
	{
		if (**format == 's')
		{
			if(yes == 1)
			{
				if (i >= j)
				{
					if (j < ft_strlen(str->s))
						k = i - j;
					else
						k = i - ft_strlen(str->s);
				}
				else
				{
					if (j < ft_strlen(str->s))
						k = i - j;
					else
						k = i - ft_strlen(str->s);
				}
			}
			else
				k = i - ft_strlen(str->s);
		}
		else if (j > ft_len(str, *format))
			k = i - j - len(str, (char *)*format);
		else
			k = i - ft_len(str, (char *)*format) -len(str, (char *)*format);
		while (--k >= 0)
			ft_putchar(' ');
		if (**format == 'd' && str->d < 0)
			ft_putchar('-');
		k = j - ft_len(str, *format);
		while (--k >= 0 && **format != 's')
			ft_putchar('0');
		print_format2(str, *format, j, yes);
	}
}

int		len(t_list *str, const char *format)
{
	while (is_format(*format) == 0)
		format++;
	if (*format == 'd' && str->d < 0)
		return (1);
	return (0);
}

int		find(char *s, char c)
{
	while (*s && is_format(*s) == 0)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	print_format2(t_list *str, const char *format, int j, int yes)
{
	char	*s;
	long	nb;

	if (*format == 'd')
	{
		if (str->d < 0)
		{
			nb = (str->d) * (-1);
			if (nb < 0)
				nb = -nb;
		}
		else
			nb = str->d;
		ft_putnbr(nb);
	}
	else if (*format == 's')
	{
		if (yes == 1)
		{
			//printf("\n it's %s\n")
			while (--j >= 0 && *(str->s))
				ft_putchar(*((str->s)++));
		}
		else
			ft_putstr(str->s);
	}
	else if (*format == 'x')
	{
		s = dec_to_hexa(str->x);
		ft_putstr(s);
		free(s);
	}
}

char	*dec_to_hexa(unsigned int n)
{
	char	reverse[int_len(n)];
	char	*converted;
	int		i;

	converted = malloc(int_len(n) + 1);
	i = 0;
	if (n == 0)
	{
		*converted = '0';
		*(converted + 1) = '\0';
		return (converted);
	}
	while (n != 0)
	{
		reverse[i++] = num_char(n % 16);
		n = n / 16;
	}
	while (--i >= 0)
	{
		converted[n++] = reverse[i];
	}
	converted[n] = '\0';
	return (converted);
}
/*
int main()
{
  int i;
  i = 0;
  char *s = NULL;
	printf("|%d|\n", 123);
	ft_printf("|%d|\n", 123);
	printf("*********************\n");
	printf("|%d|\n", 0);
	ft_printf("|%d|\n", 0);
	printf("*********************\n");
	printf("|%d|\n", 2147483647);
	ft_printf("|%d|\n", 2147483647);
	printf("*********************\n");
	printf("|%ld|\n", -2147483648);
	ft_printf("|%d|\n", -2147483648);
	printf("*********************\n");
    printf("|%5.0d|\n", -2147483648);
    ft_printf("|%5.0d|\n", 	-2147483648);
	printf("*********************\n");
	printf("Magic %s is %5d\n", "number", 26);
	ft_printf("Magic %s is %5d\n", "number", 26);
	printf("*********************\n");
	printf("%1d\n", 94);
	ft_printf("%1d\n", 94);
	printf("*********************\n");
	printf("Hexadecimal for %d is %x\n", 42, 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	//printf("this %s %1d\n", "this is a ", 42);
	ft_printf("simpl");
	printf("d11w4p %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d\n", 1, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d11w4p %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d %11.4d\n", 1, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);

  return (0);
}*/
/*
int	main()
{
	//ft_printf("~%.3s\n", "b");
	//printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "1123456789", "tjehurthteutuiehteute", "NULL");
	//ft_printf("s4p ~%.4s` ~%.4s` ~%.4s` ~%.4s` ~%.4s`\n", "", "toto", "1123456789", "tjehurthteutuiehteute", "NULL");
	//printf("********************\n");
	printf("s11w ~%11s` ~%11s` ~%11s` ~%11s` ~%11s`\n", "", "toto", "1123456789", "tjehurthteutuiehteute", "NULL");
	ft_printf("s11w ~%11s` ~%11s` ~%11s` ~%11s` ~%11s`\n", "", "toto", "1123456789", "tjehurthteutuiehteute", "NULL");


	return (0);
}*/