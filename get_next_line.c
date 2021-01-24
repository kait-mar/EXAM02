#include "get_next_line.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	if (!(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int		find(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			return (1);
		}
		i++;
	}

	return (0);
}

char	*ft_strdup(char *s1)
{
	int	i;
	char	*str;

	i = 0;
	if (s1 == 0)
		return (0);
	str = malloc(ft_strlen(s1) + 1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char *s;
	char	*buff;
	int		i;
	char	*temp;

	if (!(buff = malloc(1001)))
		return (-1);
	if (s == 0)
	{
		s = malloc(1);
		*s = '\0';
	}
	else if (s)
	{
		if (find(s))
		{
			*line = ft_strdup(s);
			int le = ft_strlen(s);
			char *tmp;
			tmp = s;
			s = ft_strdup(s + le + 1);
			free(tmp);
			free(buff);
			return (1);
		}
	}
	while ((i = read(fd, buff, 1000)) > 0)
	{
		buff[i] = '\0';
		temp = ft_strjoin(s, buff);
		if (find(temp))
		{
			*line = ft_strdup(temp);
			int to_ = ft_strlen(temp);
			char	*tmp;
			tmp = temp;
			temp = ft_strdup(temp + (to_ + 1));
			free(tmp);
			free(s);
			s = temp;
			free(buff);
			return (1);
		}
		else
		{
			free(s);
			s = temp;
		}
	}
	free(buff);
	if (s)
	{
		*line = ft_strdup(s);
		free(s);
		s = NULL;
	}
	else
		*line = ft_strdup("");
	return 0;
}