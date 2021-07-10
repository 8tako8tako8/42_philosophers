#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!philo->flag_fin && !g_flag_fin)
	{
		take_forks(philo);
		if (g_flag_fin)
			break ;
		if (eat_spaghetti(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		check_count_eat(philo->info, philo);
		drop_forks(philo);
		if (spend_sleeping(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		think_deeply(philo);
	}
	return (NULL);
}
