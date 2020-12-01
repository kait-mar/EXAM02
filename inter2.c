#include <stdio.h>
#include <unistd.h>

void ft_putchar(char c)
{
    write(1,&c,1);
}

int check_previous(char c, char *str, int i)
{
    while (i >= 0)
    {
        if (str[i] == c)
            return (1);
        i--;
    }
    return (0);
}

int main(int argc, char **argv)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (argv[1][i])
    {
        while (argv[2][j])
        {
            if (argv[1][i] == argv[2][j])
            {
                if (check_previous(argv[2][j], argv[1], i - 1))
                {
                    ft_putchar(argv[2][j]);
                    break ;
                }
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (0);
}