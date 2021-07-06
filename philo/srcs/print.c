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
	if (philo->flag_fin || g_flag_fin)
	{
		pthread_mutex_unlock(&g_print);
		return ;
	}
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
	pthread_mutex_unlock(&g_print);
}
