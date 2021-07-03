#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && \
			(str1[i] == str2[i]) && (i < n - 1))
	{
		i++;
	}
	return ((int)(str1[i]) - (int)(str2[i]));
}

int	ft_atoi(const char *str)
{
	int		number;
	int		i;

	number = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		number = number * 10;
		number += str[i] - '0';
		i++;
	}
	return (number);
}
