#include "philo.h"

int	take_forks_and_check_fin(t_philo *philo)
{
	pthread_mutex_lock(&g_fork[philo->right_fork]);
	if (g_flag_fin)
	{
		pthread_mutex_unlock(&g_fork[philo->right_fork]);
		return (FINISH);
	}
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	pthread_mutex_lock(&g_fork[philo->left_fork]);
	if (g_flag_fin)
	{
		pthread_mutex_unlock(&g_fork[philo->left_fork]);
		return (FINISH);
	}
	if (print_status_and_check_fin(philo, FORK) == ERROR)
		return (ERROR);
	return (CONTINUE);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_fork[philo->right_fork]);
	pthread_mutex_unlock(&g_fork[philo->left_fork]);
}

static int	spend_eating(t_info *info, t_philo *philo, long time_last_eat)
{
	long	time_now;

	while (1)
	{
		time_now = get_time_in_ms();
		if (time_now == ERROR)
		{
			pthread_mutex_unlock(&(philo->die));
			return (ERROR);
		}
		if ((time_now - time_last_eat) >= info->time_to_eat)
			break ;
		usleep(50);
	}
	return (SUCCESS);
}

int	eat_spaghetti(t_info *info, t_philo *philo)
{
	long	tmp;

	pthread_mutex_lock(&(philo->die));
	philo->count_eat++;
	if (print_status_and_check_fin(philo, EAT) == ERROR)
	{
		pthread_mutex_unlock(&(philo->die));
		return (ERROR);
	}
	tmp = get_time_in_ms();
	if (tmp == ERROR)
	{
		pthread_mutex_unlock(&(philo->die));
		return (ERROR);
	}
	philo->time_last_eat = tmp;
	if (spend_eating(info, philo, philo->time_last_eat) == ERROR)
	{
		pthread_mutex_unlock(&(philo->die));
		return (ERROR);
	}
	pthread_mutex_unlock(&(philo->die));
	return (SUCCESS);
}
