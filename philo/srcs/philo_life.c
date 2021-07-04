#include "philo.h"

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!philo->flag_fin && !g_flag_fin)
	{
		// printf("1: id=%d\n", philo->id);
		take_forks(philo);
		// printf("2: id=%d\n", philo->id);
		if (eat_spaghetti(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		check_count_eat(philo->info, philo);
		drop_forks(philo);
		// printf("3: id=%d\n", philo->id);
		if (spend_sleeping(philo->info, philo) == ERROR)
		{
			print_error_message(GETTIMEOFDAY_FAILED);
			break ;
		}
		// printf("4: id=%d\n", philo->id);
		think_deeply(philo);
		// printf("id: %d, flag_fin: %d, flag_eat_fin: %d, g_flag_fin: %d\n", philo->id, philo->flag_fin, philo->flag_eat_fin, g_flag_fin);
	}
	// printf("thread finish\n");
	return (NULL);
}
