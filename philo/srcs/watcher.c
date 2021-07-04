#include "philo.h"

void	*death_watcher(void *arg)
{
	t_philo	*philo;
	long	time_now;

	philo = (t_philo *)arg;
	while (!g_flag_fin)
	{
		// if (philo->flag_eat_fin)
		// 	break ;
		time_now = get_time_in_ms();
		if (time_now == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			return (NULL);
		}
		if ((time_now - philo->time_last_eat) >= philo->info->time_to_die)
		{
			print_status(philo, DIE);
			pthread_mutex_lock(&g_die);
			g_flag_fin = TRUE;
			pthread_mutex_unlock(&g_die);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
