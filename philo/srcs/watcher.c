#include "philo.h"

static void	unlock_all_forks(t_info *info)
{
	int		i;

	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_mutex_unlock(&g_fork[i]);
		i++;
	}
	i = 0;
	while (i < (info->num_of_philos))
	{
		pthread_mutex_unlock(&g_fork[i]);
		i++;
	}
}

static void	*end_abnormally(t_info *info)
{
	print_error_message(GETTIMEOFDAY_FAILED);
	switch_flag_to_fin();
	unlock_all_forks(info);
	return (NULL);
}

void	switch_flag_to_fin(void)
{
	pthread_mutex_lock(&g_fin);
	g_flag_fin = TRUE;
	pthread_mutex_unlock(&g_fin);
}

void	*death_watcher(void *arg)
{
	t_philo	*philo;
	long	time_now;

	philo = (t_philo *)arg;
	while (!g_flag_fin)
	{
		time_now = get_time_in_ms();
		if (time_now == ERROR)
			return (end_abnormally(philo->info));
		pthread_mutex_lock(&(philo->die));
		if ((time_now - philo->time_last_eat) > philo->info->time_to_die)
		{
			if (print_status_and_check_fin(philo, DIE) == ERROR)
				return (NULL);
			unlock_all_forks(philo->info);
			pthread_mutex_unlock(&(philo->die));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->die));
		usleep(200);
	}
	return (NULL);
}
