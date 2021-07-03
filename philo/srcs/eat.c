#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	print_status(philo, FORK);
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_fork[philo->right_fork]);
	pthread_mutex_unlock(&g_fork[philo->left_fork]);
}

int	eat_spaghetti(t_info *info, t_philo *philo)
{
	long	time_now;
	long	tmp;

	print_status(philo, EAT);
	philo->count_eat++;
	tmp = get_time_in_ms();
	if (tmp == ERROR)
		return (ERROR);
	while (1)
	{
		time_now = get_time_in_ms();
		if (time_now == ERROR)
			return (ERROR);
		if ((time_now - tmp) >= info->time_to_eat)
			break ;
		usleep(100);
	}
	philo->time_last_eat = time_now;
	return (SUCCESS);
}
