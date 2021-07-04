#include "philo.h"

int		does_satisfy_count_eat(t_info *info, t_philo *philo)
{
	return philo->count_eat == info->num_of_each_eating;
}

void	check_count_eat(t_info *info, t_philo *philo)
{
	if (info->num_of_each_eating != -1 && does_satisfy_count_eat(info, philo))
	{
		// philo->flag_eat_fin = TRUE;// いらないかも
		pthread_mutex_lock(&g_eat);
		info->count_all_eat++;
		pthread_mutex_unlock(&g_eat);
	}
	if (info->count_all_eat == info->num_of_philos)
	{
		pthread_mutex_lock(&g_fin);
		g_flag_fin = TRUE;
		pthread_mutex_unlock(&g_fin);
	}
}