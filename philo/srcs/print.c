#include "philo.h"

int	print_error_message(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (STATUS_ERROR);
}

void	print_status(t_philo *philo, int status)
{
	long	ms_time;

	pthread_mutex_lock(&g_print);
	ms_time = get_time_in_ms();
	if (philo->flag_eat_fin || philo->flag_fin)
		return ;
	if (status == FORK)
		ft_putstr_fd("has taken a fork\n", 1);
	else if (status == EAT)
		ft_putstr_fd("is eating\n", 1);
	else if (status == SLEEP)
		ft_putstr_fd("is sleeping\n", 1);
	else if (status == THINK)
		ft_putstr_fd("is thinking\n", 1);
	else if (status == DIE)
		ft_putstr_fd("died\n", 1);
	pthread_mutex_unlock(&g_print);
}

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