#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int width;
int prc_width;
int specifer;
int pc;

void ft_crear()
{
    width = 0;
    prc_width = -1;
    specifer = 0;
}
int ft_strlen(char *str)
{
    int i =0;
    while (str[i])
    {
        i++;
    }
    return (i);
    
}
void ft_putchar(char c)
{
    write(1, &c, 1);
    pc++;
}

void ft_putstr(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        write(1, &str[i], 1);
        i++;
        pc++;
    }
}

void ft_putspecstr(char *str, int len)
{
    int i = 0;
    while(len > 0)
    {
        write(1, &str[i], 1);
        len--;
        i++;
        pc++;
    }
}
int ft_atoi(const char *str)
{
    int i = 0;
    long a = 0;
    int s = 1;

    while (str[i] >= 8 && str[i] <= 13)
    {
        if (str[i] == 27)
            return (0);
        i++;
    }
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            s = -1;
        i++;
    }
    while (str[i] >= 48 && str[i] <= 57)
        a = a * 10 + str[i++] - 48;
    if (a > 9223372036854775807)
    {
        if (s == -1)
			return (0);
		else if (s == 1)
			return (-1);
    }
    return(a * s);
}

int len_num(long nbr)
{
    int count;
    count = 0;
    if (nbr >= 0 && nbr <=9)
        return (1);
    if (nbr < 0)
    {
        nbr *= -1;
        count++;
    }
    while(nbr)
    {
        nbr/=10;
        count++;
    }
    return (count);
}

void ft_putnbr(long nbr)
{
    if(nbr < 0)
    {
        ft_putchar('-');
        nbr *= -1;
    }
    if(nbr >= 10)
    {
        ft_putnbr(nbr / 10);
        ft_putchar(nbr % 10 + 48);
    }
    else
        ft_putchar(nbr + 48);
}
void ft_cnv_d_to_hex(unsigned int nbr)
{
    if(nbr > 0)
    {
        ft_cnv_d_to_hex(nbr / 16);
        if (nbr % 16 > 9)
            ft_putchar(nbr % 16 + 87);
        else if (nbr % 16 <= 9)
            ft_putchar(nbr % 16 + 48);
        
    }  
}

int len_hex(unsigned int nbr)
{
    int count = 0;
    if (nbr == 0)
        return 1;
    while (nbr > 0)
    {
        nbr /= 16;
        count++;
    }
    return(count);
}

void ft_getaftermod(const char **fmt)
{
    
    ft_crear();
    *fmt = *fmt + 1;
    while (**fmt != '\0')
	{
        if (**fmt == '.')
        {
            if (*(*fmt + 1) >= '0' && *(*fmt + 1) <= '9')
                prc_width = ft_atoi(*fmt + 1);
            else 
                prc_width = 0;
            while (*(*fmt + 1) >= '0' && *(*fmt + 1) <= '9')
                *fmt = *fmt + 1;
        }
        else if (**fmt >= '0' && **fmt <= '9')
        {
             width = ft_atoi(*fmt);
            while (*(*fmt + 1) >= '0' && *(*fmt + 1) <= '9')
                *fmt = *fmt + 1;
        }
        else
        {
            specifer = **fmt;
            break;
        }
    *fmt = *fmt + 1;    
    }
}

void ft_width_trick(int len, char c)
{
    int i;
    i = 0;
    if (len > 0)
    {
        while (i < len)
        {
            pc++;
            write(1, &c, 1);
            i++;
        }
    }
}

void handle_string(char *str)
{
    int l = 0;
    if (!str)
        str = "(null)";
    l = ft_strlen(str);
    if (width >= prc_width)
    {
        if(prc_width <= l && prc_width >= 0)
        {
            ft_width_trick(width - prc_width, ' ');
            ft_putspecstr(str, prc_width);
        }
        else
            ft_width_trick(width - l, ' ');
    }
    else if (width < prc_width && prc_width > l)
            ft_width_trick(width - l, ' ');
    else if (prc_width <= l)
    {
        ft_putspecstr(str, prc_width);
    }
    if (prc_width > l || prc_width == -1 )
        ft_putstr(str);
}

void handle_int(long nbr)
{
    int l;

    if(nbr == 0 && prc_width == 0)
        l = 0;
    else
        l = len_num(nbr);
        if (width <= prc_width && prc_width > l)
            ft_width_trick(prc_width - l, '0');
        else if (width > prc_width && prc_width <= l)
            ft_width_trick(width - l, ' ');
        else if (width > prc_width && prc_width > l)
        {
            ft_width_trick(width - prc_width, ' ');
            ft_width_trick(prc_width - l, '0');
        }
        if (!(nbr == 0 && prc_width == 0))
            ft_putnbr(nbr);
}
void handle_x(unsigned int nbr)
{
    int l;

    if(nbr == 0 && prc_width == 0)
        l = 0;
    else
        l = len_hex(nbr);
        if (width <= prc_width && prc_width > l)
            ft_width_trick(prc_width - l, '0');
        else if (width > prc_width && prc_width <= l)
            ft_width_trick(width - l, ' ');
        else if (width > prc_width && prc_width > l)
        {
            ft_width_trick(width - prc_width, ' ');
            ft_width_trick(prc_width - l, '0');
        }
        if (nbr == 0 && prc_width != 0)
            ft_putchar(nbr + 48);
        else if (!(nbr == 0 && prc_width == 0))
            ft_cnv_d_to_hex(nbr);
}
void handle_percent(const char **fmt, va_list argptr)
{ 
   
    ft_getaftermod(fmt);
    if (specifer == 's')
        handle_string(va_arg(argptr, char *));
    else if (specifer == 'd')
        handle_int(va_arg(argptr, int));
     else if (specifer == 'x')
         handle_x(va_arg(argptr, unsigned int));
    else
        ft_putchar(specifer);
}
int ft_printf(const char *fmt, ...)
{
    va_list argptr;

    va_start(argptr, fmt);
    
    pc = 0;
    while (*fmt != '\0')
    {
        if(*fmt == '%' && *(fmt + 1) != '%')
            handle_percent(&fmt, argptr);
        else
			ft_putchar(*fmt);
        fmt++;
    }
    va_end(argptr);
    return(pc);
}

// int main()
// {

// 	printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
// 	ft_printf("s10w10p ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s` ~%10.10s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);

// }