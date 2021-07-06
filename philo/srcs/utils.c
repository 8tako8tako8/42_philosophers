#include "philo.h"

int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (ERROR);
	i = 1;
	while (argv[i])
	{
		if (!is_positive_number(argv[i]))
			return (ERROR);
		if (!is_integer(1, argv[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
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

int	is_positive_number(char *str)
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
