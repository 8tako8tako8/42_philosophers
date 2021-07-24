#include "philo.h"

static int	does_satisfy_count_eat(t_info *info, t_philo *philo)
{
	return (philo->count_eat == info->num_of_each_eating);
}

void	check_count_eat(t_info *info, t_philo *philo)
{
	if (info->num_of_each_eating != -1 && does_satisfy_count_eat(info, philo))
	{
		pthread_mutex_lock(&g_eat);
		info->count_all_eat++;
		if (info->count_all_eat == info->num_of_philos)
		{
			switch_flag_to_fin();
			unlock_all_forks(info);
		}
		pthread_mutex_unlock(&g_eat);
	}
}
