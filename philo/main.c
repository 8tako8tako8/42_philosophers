#include <stdio.h>

#define VALID 1
#define INVALID -1

typedef struct s_info
{
	int			num_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_eating;
}				t_info;

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

int	is_integer(int sign, char *number)
{
	int	digit;

	digit = 0;
	while ('0' <= number[digit] && number[digit] <= '9')
		digit++;
	if (digit > 10)
		return (0);
	if (sign == 1 && ft_strncmp(number, "2147483647", 10) > 0 && digit == 10)
		return (0);
	if (sign == -1 && ft_strncmp(number, "2147483648", 10) > 0 && digit == 10)
		return (0);
	return (1);
}

int is_number(char *str)
{
	int	i;

	if (str[0] < '1' || '9' < str[0])
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (0);
		i++;
	}
	return (1);
}

int check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (INVALID);
	i = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (INVALID);
		if (!is_integer(1, argv[i]))
			return (INVALID);
		i++;
	}
	return (VALID);
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

void	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->num_of_eating = -1;
	if (argc == 6)
		info->num_of_eating = ft_atoi(argv[5]);
}



void	print_info(t_info *info)
{
	printf("1: %d", info->num_of_philo);
	printf("2: %d", info->time_to_die);
	printf("3: %d", info->time_to_eat);
	printf("4: %d", info->time_to_sleep);
	printf("5: %d", info->num_of_eating);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_arguments(argc, argv) == -1)
		printf("Invalid argument\n");
	init_info(&info, argc, argv);
	print_info(&info);
}
