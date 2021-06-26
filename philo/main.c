#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define STATUS_SUCCESS 0
#define STATUS_ERROR 1

#define SUCCESS 1
#define ERROR -1

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DIE 4

typedef struct s_info
{
	int			num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_of_each_eating;
}				t_info;

typedef struct s_philo
{
	int			id;
	int			count_eat;
	long		time_start;//いらない？
	long		time_last_eat;
	long		time_passed;//いらない？
	int			right_fork;
	int			left_fork;
	pthread_t	thread;
	t_info		*info;
}				t_philo;

pthread_mutex_t *g_fork;

long	print_status(t_philo *philo, int status)
{
	long	ms_time;

	ms_time = get_time_in_ms();
	if (status == FORK)
		printf("%ld %d has taken a fork\n", ms_time, philo->id);
	else if (status == EAT)
		printf("%ld %d is eating\n", ms_time, philo->id);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", ms_time, philo->id);
	else if (status == THINK)
		printf("%ld %d is thinking\n", ms_time, philo->id);
	else if (status == DIE)
		printf("%ld %d died\n", ms_time, philo->id);
	return (ms_time);
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
		return (ERROR);
	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (ERROR);
		if (!is_integer(1, argv[i]))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
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

long	get_time_in_ms(void)
{
	struct timeval	tv;
	time_t			time_ms;

	if (gettimeofday(&tv, NULL) < 0)
		return (ERROR);
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms);
}

int	init_info(t_info *info, int argc, char **argv)
{
	info->num_of_philos = ft_atoi(argv[1]);
	if (info->num_of_philos == 1)
		return (ERROR);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->num_of_each_eating = -1;
	if (argc == 6)
		info->num_of_each_eating = ft_atoi(argv[5]);
	return (SUCCESS);
}

int	init_global_variables(t_info *info)
{
	g_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (info->num_of_philos + 1));
	if (!g_fork)
		return (ERROR);
	return (SUCCESS);
}

int	print_error_message(char *str)
{
	printf("%s\n", str);
	return (STATUS_ERROR);
}

t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;
	long	time_start;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philos + 1));
	if (!philo)
		return (NULL);
	time_start = get_time_in_ms();
	if (time_start == ERROR)
		return (NULL);
	i = 0;
	while (i <= (info->num_of_philos))
	{
		philo[i].id = i;
		philo[i].count_eat = 0;
		philo[i].time_start = time_start;
		philo[i].time_last_eat = 0;
		philo[i].time_passed = 0;
		philo[i].right_fork = i;
		if (i == info->num_of_philos)
			philo[i].left_fork = 1;
		else
			philo[i].left_fork = i + 1;
		philo[i].info = info;
		i++;
	}
	return (philo);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	print_status(philo, FORK);
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	print_status(philo, FORK);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (1)
	{
		take_forks(philo);
		//eat_spaghetti();
		//spend_sleeping();
	}
}

int	create_threads(t_info *info, t_philo *philos)
{
	int	i;

	i = 1;
	while (i <= (info->num_of_philos))
	{
		if (pthread_create(&(philos[i].thread), NULL, &philo_life, &(philos[i])) != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	join_threads(t_info *info, t_philo *philos)
{
	int	i;

	i = 1;
	while (i <= (info->num_of_philos))
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (check_arguments(argc, argv) == ERROR)
		return (print_error_message("invalid argument"));
	if (init_info(&info, argc, argv) == ERROR)
		return (print_error_message("only one philosoher"));
	if (init_global_variables(&info) == ERROR)
		return (print_error_message("system call fail"));
	philos = init_philo(&info);
	if (!philos)
		return (print_error_message("system call fail\n"));
/* 	if (create_threads(&info, philos) == ERROR)
		return (print_error_message("system call fail\n"));
	join_threads(&info, philos); */
}

/* void	print_info(t_info *info)
{
	printf("1: %d\n", info->num_of_philos);
	printf("2: %d\n", info->time_to_die);
	printf("3: %d\n", info->time_to_eat);
	printf("4: %d\n", info->time_to_sleep);
	printf("5: %d\n", info->num_of_each_eating);
	printf("6: %p\n", info);
}

void	print_philo(t_philo *philo, t_info *info)
{
	int	i = 0;

	while (i <= (info->num_of_philos))
	{
		printf("1: %d\n", philo[i].id);
		printf("2: %d\n", philo[i].count_eat);
		printf("3: %ld\n", philo[i].time_start);
		printf("4: %ld\n", philo[i].time_last_eat);
		printf("5: %ld\n", philo[i].time_passed);
		printf("6: %d\n", philo[i].right_fork);
		printf("7: %d\n", philo[i].left_fork);
		printf("8: %p\n", philo[i].info);
		i++;
	}
} */
