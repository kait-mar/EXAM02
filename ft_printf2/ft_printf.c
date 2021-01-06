#include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int g_counter;
typedef struct s_list
{
	int             d;
	char            *s;
	unsigned int    x;
}				t_list;

int     ft_printf(const char *format, ...);
void    ft_putchar(char c);
char    char_num(int n);
char	*dec_to_hexa(unsigned long long n);
void	ft_putnbr(int n);
void	ft_putstr(char *str);
void    print_format(t_list *structure, const char *format);
int     is_format(char c);
void    const_struct(t_list *structure, va_list list, const char *format);
void	print(t_list *structure, const char **format);
int		unsign_lenght(unsigned long long n);
int		ft_isdigit(char c);
void	print_width(t_list *structure, const char **format);
int		lenght(int n);
int		ft_lenght(t_list *structure, const char *format);
void    print_prec(t_list *structure, const char **format);
int     ft_atoi(char *num);
int		ft_strlen(char *str);
void	ft_putnbr2(int n);
int		ft_lenght3(t_list *structure, const char *format);
void    print_format2(t_list *structure, const char *format);
int     find(const char *str, char c);

int		ft_printf(const char *format, ...)
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
	j = ft_atoi(width);
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
		if (**format == 'd' && structure->d < 0)
			k--;
		while (--k >= 0)
			ft_putchar(' ');
		if (**format == 'd' && structure->d < 0)
			ft_putchar('-');
		if (!(i != 0 && **format == 's'))
		{
			k = i - ft_lenght(structure, *format);
			while (--k >= 0)
				ft_putchar('0');
		}
		print_format2(structure, *format);
	}
}

void	const_struct(t_list *structure, va_list list, const char *format)
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

void	print_format(t_list *structure, const char *format)
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

void	print_format2(t_list *structure, const char *format)
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
		n *= -1;
		ft_putchar('-');
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

void	ft_putnbr2(int n)
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

void	ft_putchar(char c)
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

char	char_num(int n)
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
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
	}
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int		is_format(char c)
{
	if (c == 'd' || c == 'x' || c == 's')
		return (1);
	else
		return (0);
}

int		find(const char *str, char c)
{
	while (*str && *str != '%')
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int		ft_atoi(char *num)
{
	int 	i;
	int		n;

	i = 0;
	n = 0;
	while (num[i])
	{
		n = n * 10 + ((num[i] - '0') % 10);
		i++;
	}
	return (n);
}

int		ft_lenght(t_list *structure, const char *format)
{
	char	*s;
	int		i;

	if (*format == 's')
		return (ft_strlen(structure->s));
	if (*format == 'd')
		return (lenght(structure->d));
	if (*format == 'x')
	{
		s = dec_to_hexa(structure->x);
		i = ft_strlen(s);
		free(s);
		return (i);
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		ft_lenght3(t_list *structure, const char *format)
{
	if (*format == 's')
		return (0);
	if (*format == 'd' && structure->d < 0)
		return (1);
	if (*format == 'd')
		return (0);
	if (*format == 'x')
		return (0);
	return (0);
}

int main()
{
  int i;
  i = 0;
  char *s = NULL;
   // printf("hello world %s, yes %5.5x %s\n", s, -5485846, s);
    ft_printf("hello world, yes %15.9x %d\n", 0, 3);
    printf("hello world, yes %15.9x %d\n", 0, 3);
    
  // printf("|%5.3d|\n", 6);
  //precision avec s et x
  //while (1)
  //  i++;
  return (0);
}