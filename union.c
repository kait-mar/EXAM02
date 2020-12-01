#include <unistd.h>
void ft_putchar(char c)
{
    write(1,&c,1);
}

int ft_check(char c, char* string, int i)
{
    while (i >= 0)
    {
       if(string[i] == c)
           return 1;    
      i--;
    }
  return 0;
}

int main(int argc, char **argv)
{
    int i;
    int j;
    i = 0;
    j = 0;
    if(argc == 3)
    {
        while (argv[1][i])
        {
            if(ft_check(argv[1][i],argv[1], i-1) == 0){
                  ft_putchar(argv[1][i]);  
            }
               i++;  
        } 
         while (argv[2][j])
        {
            if((ft_check(argv[2][j],argv[2], j-1) == 0) && (ft_check(argv[2][j],argv[1], i) == 0 ))
            {
                 ft_putchar(argv[2][j]);  
            }
            j++;   
        } 
        ft_putchar('\n');      
    }else
          ft_putchar('\n');
}
