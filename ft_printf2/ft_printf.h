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

#endif