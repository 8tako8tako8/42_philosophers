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

#define TRUE 1
#define FALSE 0

#define INVALID_ARGUMENT "invalid argument"
#define ONLY_ONE_PHILO "only one philosoher"
#define MALLOC_FAILED "malloc failed"
#define GETTIMEOFDAY_FAILED "gettimeofday failed"
#define MALLOC_OR_GETTIMEOFDAY_FAILED "malloc or gettimeofday failed"
#define PTHREAD_CREATE_FAILED "pthread create failed"

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
	int			flag_eat_fin;
	int			flag_fin;
	long		time_last_eat;
	int			right_fork;
	int			left_fork;
	pthread_t	thread;
	pthread_t	watcher;
	t_info		*info;
}				t_philo;

pthread_mutex_t	*g_fork;
pthread_mutex_t	g_print;//いらないかも
pthread_mutex_t	g_die;
pthread_t		g_watcher;
int				g_flag_fin;

// long	get_time_in_ms(void)
// {
// 	struct timeval	tv;
// 	time_t			time_ms;

// 	if (gettimeofday(&tv, NULL) < 0)
// 		return (ERROR);
// 	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
// 	return (time_ms);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t		i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (s)
// 		write(fd, s, ft_strlen(s));
// }

// void	ft_putendl_fd(char *s, int fd)
// {
// 	ft_putstr_fd(s, fd);
// 	ft_putstr_fd("\n", fd);
// }

// int	print_error_message(char *str)
// {
// 	ft_putendl_fd(str, STDERR_FILENO);
// 	return (STATUS_ERROR);
// }

// void	print_status(t_philo *philo, int status)
// {
// 	long	ms_time;

// 	pthread_mutex_lock(&g_print);
// 	ms_time = get_time_in_ms();
// 	if (philo->flag_eat_fin || philo->flag_fin)
// 		return ;
// 	if (status == FORK)
// 		printf("%ld %d has taken a fork\n", ms_time, philo->id);
// 	else if (status == EAT)
// 		printf("%ld %d is eating\n", ms_time, philo->id);
// 	else if (status == SLEEP)
// 		printf("%ld %d is sleeping\n", ms_time, philo->id);
// 	else if (status == THINK)
// 		printf("%ld %d is thinking\n", ms_time, philo->id);
// 	else if (status == DIE)
// 		printf("%ld %d died\n", ms_time, philo->id);
// 	pthread_mutex_unlock(&g_print);
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	unsigned char	*str1;
// 	unsigned char	*str2;
// 	size_t			i;

// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	if (n == 0)
// 		return (0);
// 	i = 0;
// 	while (str1[i] && str2[i] && \
// 			(str1[i] == str2[i]) && (i < n - 1))
// 	{
// 		i++;
// 	}
// 	return ((int)(str1[i]) - (int)(str2[i]));
// }

// int	is_integer(int sign, char *number)
// {
// 	int	digit;

// 	digit = 0;
// 	while ('0' <= number[digit] && number[digit] <= '9')
// 		digit++;
// 	if (digit > 10)
// 		return (0);
// 	if (sign == 1 && ft_strncmp(number, "2147483647", 10) > 0 && digit == 10)
// 		return (0);
// 	if (sign == -1 && ft_strncmp(number, "2147483648", 10) > 0 && digit == 10)
// 		return (0);
// 	return (1);
// }

// int is_number(char *str)
// {
// 	int	i;

// 	if (str[0] < '1' || '9' < str[0])
// 		return (0);
// 	i = 1;
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || '9' < str[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int check_arguments(int argc, char **argv)
// {
// 	int	i;

// 	if (argc != 5 && argc != 6)
// 		return (ERROR);
// 	i = 1;
// 	while (argv[i])
// 	{
// 		if (!is_number(argv[i]))
// 			return (ERROR);
// 		if (!is_integer(1, argv[i]))
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// int	ft_atoi(const char *str)
// {
// 	int		number;
// 	int		i;

// 	number = 0;
// 	i = 0;
// 	while ('0' <= str[i] && str[i] <= '9')
// 	{
// 		number = number * 10;
// 		number += str[i] - '0';
// 		i++;
// 	}
// 	return (number);
// }

// int	init_info(t_info *info, int argc, char **argv)
// {
// 	info->num_of_philos = ft_atoi(argv[1]);
// 	if (info->num_of_philos == 1)
// 		return (ERROR);
// 	info->time_to_die = ft_atoi(argv[2]);
// 	info->time_to_eat = ft_atoi(argv[3]);
// 	info->time_to_sleep = ft_atoi(argv[4]);
// 	if (argc == 5)
// 		info->num_of_each_eating = -1;
// 	if (argc == 6)
// 		info->num_of_each_eating = ft_atoi(argv[5]);
// 	return (SUCCESS);
// }

// int	init_global_variables(t_info *info)
// {
// 	int		i;

// 	g_flag_fin = FALSE;
// 	pthread_mutex_init(&g_print, NULL);
// 	pthread_mutex_init(&g_die, NULL);
// 	g_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (info->num_of_philos + 1));
// 	if (!g_fork)
// 		return (ERROR);
// 	i = 1;
// 	while (i <= (info->num_of_philos))
// 	{
// 		pthread_mutex_init(&g_fork[i], NULL);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// t_philo	*init_philo(t_info *info)
// {
// 	t_philo	*philo;
// 	long	time_start;
// 	int		i;

// 	philo = (t_philo *)malloc(sizeof(t_philo) * (info->num_of_philos + 1));
// 	if (!philo)
// 		return (NULL);
// 	time_start = get_time_in_ms();
// 	if (time_start == ERROR)
// 		return (NULL);
// 	i = 0;
// 	while (i <= (info->num_of_philos))
// 	{
// 		philo[i].id = i;
// 		philo[i].count_eat = 0;
// 		philo[i].flag_eat_fin = FALSE;
// 		philo[i].flag_fin = FALSE;
// 		philo[i].time_last_eat = time_start;
// 		philo[i].right_fork = i;
// 		if (i == info->num_of_philos)
// 			philo[i].left_fork = 1;
// 		else
// 			philo[i].left_fork = i + 1;
// 		philo[i].info = info;
// 		i++;
// 	}
// 	return (philo);
// }

// void	take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(&g_fork[philo->right_fork]);
// 	print_status(philo, FORK);
// 	pthread_mutex_lock(&g_fork[philo->left_fork]);
// 	print_status(philo, FORK);
// }

// void	drop_forks(t_philo *philo)
// {
// 	pthread_mutex_unlock(&g_fork[philo->right_fork]);
// 	pthread_mutex_unlock(&g_fork[philo->left_fork]);
// }

// int	eat_spaghetti(t_info *info, t_philo *philo)
// {
// 	long	time_now;
// 	long	tmp;

// 	print_status(philo, EAT);
// 	philo->count_eat++;
// 	tmp = get_time_in_ms();
// 	if (tmp == ERROR)
// 		return (ERROR);
// 	while (1)
// 	{
// 		time_now = get_time_in_ms();
// 		if (time_now == ERROR)
// 			return (ERROR);
// 		if ((time_now - tmp) >= info->time_to_eat)
// 			break ;
// 		usleep(100);
// 	}
// 	philo->time_last_eat = time_now;
// 	return (SUCCESS);
// }

// int	spend_sleeping(t_info *info, t_philo *philo)
// {
// 	long	time_now;
// 	long	tmp;

// 	print_status(philo, SLEEP);
// 	tmp = get_time_in_ms();
// 	if (tmp == ERROR)
// 		return (ERROR);
// 	while (1)
// 	{
// 		time_now = get_time_in_ms();
// 		if (time_now == ERROR)
// 			return (ERROR);
// 		if ((time_now - tmp) >= info->time_to_sleep)
// 			break ;
// 		usleep(100);
// 	}
// 	return (SUCCESS);
// }

// void	think_deeply(t_philo *philo)
// {
// 	print_status(philo, THINK);
// }

// int		does_satisfy_count_eat(t_info *info, t_philo *philo)
// {
// 	return philo->count_eat == info->num_of_each_eating;
// }

// void	*philo_life(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 1)
// 		usleep(200);
// 	while (!philo->flag_fin && !philo->flag_eat_fin)
// 	{
// 		// printf("1: id=%d\n", philo->id);
// 		if (philo->id == 1)
// 			write(1, "#1\n", 3);
// 		else
// 			write(1, "$1\n", 3);
// 		take_forks(philo);
// 		// printf("2: id=%d\n", philo->id);
// 		if (philo->id == 1)
// 			write(1, "#2\n", 3);
// 		else
// 			write(1, "$2\n", 3);
// 		if (eat_spaghetti(philo->info, philo) == ERROR)
// 		{
// 			print_error_message(GETTIMEOFDAY_FAILED);
// 			break ;
// 		}
// 		if (philo->info->num_of_each_eating && does_satisfy_count_eat(philo->info, philo))
// 			philo->flag_eat_fin = TRUE;
// 		drop_forks(philo);
// 		// printf("3: id=%d\n", philo->id);
// 		if (philo->id == 1)
// 			write(1, "#3\n", 3);
// 		else
// 			write(1, "$3\n", 3);
// 		if (spend_sleeping(philo->info, philo) == ERROR)
// 		{
// 			print_error_message(GETTIMEOFDAY_FAILED);
// 			break ;
// 		}
// 		// printf("4: id=%d\n", philo->id);
// 		if (philo->id == 1)
// 			write(1, "#4\n", 3);
// 		else
// 			write(1, "$4\n", 3);
// 		think_deeply(philo);
// 	}
// 	return (NULL);
// }

// void	*philo_life(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;
// 	if (philo->id % 2 == 1)
// 		usleep(200);
// 	while (!philo->flag_fin && !philo->flag_eat_fin)
// 	{
// 		take_forks(philo);
// 		if (eat_spaghetti(philo->info, philo) == ERROR)
// 		{
// 			print_error_message(GETTIMEOFDAY_FAILED);
// 			break ;
// 		}
// 		if (philo->info->num_of_each_eating && does_satisfy_count_eat(philo->info, philo))
// 			philo->flag_eat_fin = TRUE;
// 		drop_forks(philo);
// 		if (spend_sleeping(philo->info, philo) == ERROR)
// 		{
// 			print_error_message(GETTIMEOFDAY_FAILED);
// 			break ;
// 		}
// 		think_deeply(philo);
// 	}
// 	return (NULL);
// }

// void	*watcher(void *arg)
// {
// 	t_philo	*philo;
// 	long	time_now;

// 	philo = (t_philo *)arg;
// 	while (!g_flag_fin)
// 	{
// 		if (philo->flag_eat_fin)
// 		{
// 			printf("id=%d eat fin\n", philo->id);
// 			break ;
// 		}
// 		time_now = get_time_in_ms();
// 		if (time_now == ERROR)
// 		{
// 			print_error_message(GETTIMEOFDAY_FAILED);
// 			return (NULL);
// 		}
// 		if ((time_now - philo->time_last_eat) >= philo->info->time_to_die)
// 		{
// 			print_status(philo, DIE);
// 			pthread_mutex_lock(&g_die);
// 			g_flag_fin = TRUE;
// 			pthread_mutex_unlock(&g_die);
// 			return (NULL);
// 		}
// 		usleep(200);
// 	}
// 	return (NULL);
// }

// int	create_threads(t_info *info, t_philo *philos)
// {
// 	int	i;

// 	i = 1;
// 	while (i <= (info->num_of_philos))
// 	{
// 		if (pthread_create(&(philos[i].thread), NULL, &philo_life, (void *)&(philos[i])) != 0)
// 			return (ERROR);
// 		i++;
// 	}
// 	i = 1;
// 	while (i <= (info->num_of_philos))
// 	{
// 		if (pthread_create(&(philos[i].watcher), NULL, &watcher, (void *)&(philos[i])) != 0)
// 			return (ERROR);
// 		i++;
// 	}
// 	return (SUCCESS);
// }

// void	join_threads(t_info *info, t_philo *philos)
// {
// 	int	i;

// 	i = 1;
// 	while (i <= (info->num_of_philos))
// 	{
// 		pthread_join(philos[i].thread, NULL);
// 		i++;
// 	}
// 	i = 1;
// 	while (i <= (info->num_of_philos))
// 	{
// 		pthread_join(philos[i].watcher, NULL);
// 		i++;
// 	}
// }

// void	print_philo(t_philo *philo, t_info *info)
// {
// 	int	i = 0;

// 	while (i <= (info->num_of_philos))
// 	{
// 		printf("1: %d\n", philo[i].id);
// 		printf("2: %d\n", philo[i].count_eat);
// 		// printf("3: %ld\n", philo[i].time_start);
// 		printf("4: %ld\n", philo[i].time_last_eat);
// 		// printf("5: %ld\n", philo[i].time_passed);
// 		printf("6: %d\n", philo[i].right_fork);
// 		printf("7: %d\n", philo[i].left_fork);
// 		printf("8: %p\n", philo[i].info);
// 		i++;
// 	}
// }

void	clean_mutex(t_info *info)
{
	int	i;

	i = 1;
	while (i <= (info->num_of_philos))
	{
		pthread_mutex_destroy(&g_fork[i]);
		i++;
	}
	free(g_fork);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (check_arguments(argc, argv) == ERROR)
		return (print_error_message(INVALID_ARGUMENT));
	if (init_info(&info, argc, argv) == ERROR)
		return (print_error_message(ONLY_ONE_PHILO));
	if (init_global_variables(&info) == ERROR)
		return (print_error_message(MALLOC_FAILED));
	philos = init_philo(&info);
	if (!philos)
		return (print_error_message(MALLOC_OR_GETTIMEOFDAY_FAILED));
	if (create_threads(&info, philos) == ERROR)
		return (print_error_message(PTHREAD_CREATE_FAILED));
	join_threads(&info, philos);
	write(1, "finish", 6);
	//clean_mutex(&info);
	return (0);
}

/* void	print_info(t_info *info)
{
	printf("1: %d\n", info->num_of_philos);
	printf("2: %d\n", info->time_to_die);
	printf("3: %d\n", info->time_to_eat);
	printf("4: %d\n", info->time_to_sleep);
	printf("5: %d\n", info->num_of_each_eating);
	printf("6: %p\n", info);
} */
