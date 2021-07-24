#include "philo.h"

static void	print_status(int status, long long ms_time, t_philo *philo)
{
	if (status == FORK)
		printf("%lld %d has taken a fork\n", ms_time, philo->id);
	else if (status == EAT)
	{
		printf("%lld %d is eating\n", ms_time, philo->id);
		check_count_eat(philo->info, philo);
	}
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n", ms_time, philo->id);
	else if (status == THINK)
		printf("%lld %d is thinking\n", ms_time, philo->id);
	else if (status == DIE)
	{
		printf("%lld %d died\n", ms_time, philo->id);
		switch_flag_to_fin();
	}
}

static int	check_fin(void)
{
	pthread_mutex_lock(&g_fin);
	if (g_flag_fin)
	{
		pthread_mutex_unlock(&g_print);
		pthread_mutex_unlock(&g_fin);
		return (FINISH);
	}
	pthread_mutex_unlock(&g_fin);
	return (CONTINUE);
}

int	print_status_and_check_fin(t_philo *philo, int status)
{
	long long	ms_time;

	pthread_mutex_lock(&g_print);
	if (check_fin() == FINISH)
		return (SUCCESS);
	ms_time = get_time_in_ms();
	if (ms_time == ERROR)
		return (ERROR);
	print_status(status, ms_time, philo);
	pthread_mutex_unlock(&g_print);
	return (SUCCESS);
}

int	print_error_message(char *str)
{
	ft_putendl_fd(str, STDERR);
	return (STATUS_ERROR);
}
